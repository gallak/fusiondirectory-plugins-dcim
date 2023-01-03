<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)
  Copyright (C) 2016-2017  FusionDirectory

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */


class componentDcim extends simplePlugin
{

  protected $displayHeader  = TRUE;
  protected $loaded = FALSE;

  static function plInfo (): array
  {
    return [
      'plShortName'   => _('DCIM Component'),
      'plDescription' => _('DCIM Component'),
      'plPriority'    => 30,
      'plObjectClass' => ['fdDcimComponent'],
      'plObjectType'  => ['workstation','server','component'],
      'plProvidedAcls'  => parent::generatePlProvidedAcls(static::getAttributesInfo())
    ];
  }



  static function getAttributesInfo (): array
  {
    global $config;
    return [

      'CommonComponent' => [
        'name'  => _('Common component'),
        'attrs' => [
            new SelectAttribute(
                  _('Type'), _('Type of component'),
                  'fdDcimComponentType', TRUE,[],'',[]),
            new IntAttribute(
                  _('Start sequence'), _('Start sequence'),
                  'fdDcimComponentStartSequence', FALSE,0,10,1),
            new IntAttribute(
                  _('Stop sequence'), _('Stop sequence'),
                  'fdDcimComponentStopSequence', FALSE,0,10,1),
        ],
      ],

      'DedicatedComponent' => [
        'name'  => _('Dedicated component'),
        'attrs' => [ 
            new dcimCabinetSelectAttribute(
                  _('Cabinet name'), _('Cabinet Name'),
                  'fdDcimComponentCabinetId', FALSE),
            new IntAttribute(
                  _('Size'), _('Size of the Component'),
                  'fdDcimComponentSize', FALSE,0,42,1),
            new IntAttribute(
                  _('Position'), _('Position of the Component'),
                  'fdDcimComponentPosition', FALSE,0,42,1),
            new ImageAttribute(
                  _('Image of front'), _('Image of the component Front'),
                  'fdDcimComponentFrontImage', FALSE,
                  $config->get_cfg_value('MaxAvatarSize', 200), $config->get_cfg_value('MaxAvatarSize', 200), 'jpeg'),  
            new ImageAttribute(
                  _('Image of back'), _('Image of the component Back'),
                  'fdDcimComponentRearImage', FALSE,
                  $config->get_cfg_value('MaxAvatarSize', 200), $config->get_cfg_value('MaxAvatarSize', 200), 'jpeg'),
            new ObjectSelectAttribute(
                  _('Management server'), _('Management server'),
                  'fdDcimVirtualManagementServer', FALSE,
                  ['Server']),
        ],
      ],
    ];
  }


public function hostTypesChanged(){
  // show correct interface following host type
  if ($this->fdDcimComponentType == "virtual"){
    $this->attributesAccess['fdDcimComponentCabinetId']->setVisible(FALSE);
    $this->attributesAccess['fdDcimComponentCabinetId']->setValue(FALSE);
    $this->attributesAccess['fdDcimComponentSize']->setVisible(FALSE);
    $this->attributesAccess['fdDcimComponentSize']->setValue(FALSE);
    $this->attributesAccess['fdDcimComponentPosition']->setVisible(FALSE);
    $this->attributesAccess['fdDcimComponentPosition']->setValue(FALSE);
    $this->attributesAccess['fdDcimComponentFrontImage']->setVisible(FALSE);
    $this->attributesAccess['fdDcimComponentFrontImage']->setValue(FALSE);
    $this->attributesAccess['fdDcimComponentRearImage']->setVisible(FALSE);
    $this->attributesAccess['fdDcimComponentRearImage']->setValue(FALSE);
    $this->attributesAccess['fdDcimVirtualManagementServer']->setVisible(TRUE);
  }
  if ($this->fdDcimComponentType == "physical"){
    $this->attributesAccess['fdDcimComponentCabinetId']->setVisible(TRUE);
    $this->attributesAccess['fdDcimComponentSize']->setVisible(TRUE);
    $this->attributesAccess['fdDcimComponentPosition']->setVisible(TRUE);
    $this->attributesAccess['fdDcimComponentFrontImage']->setVisible(TRUE);
    $this->attributesAccess['fdDcimComponentRearImage']->setVisible(TRUE);
    $this->attributesAccess['fdDcimVirtualManagementServer']->setVisible(FALSE);
    $this->attributesAccess['fdDcimVirtualManagementServer']->setValue(FALSE);
  }


  
}

  function __construct ($dn = NULL, $object = NULL, $parent = NULL, $mainTab = FALSE)
  {
 
    parent::__construct($dn, $object, $parent, $mainTab);

    $hostTypes=['physical','virtual'];
    $this->attributesAccess['fdDcimComponentType']->setChoices($hostTypes);
    $this->attributesAccess['fdDcimComponentType']->setSubmitForm('hostTypesChanged');
  }

  public function render (): string
  {
    $smarty = get_smarty();
    return parent::render();
  }

  public function cabinetContent ($cabinet_dn): array
  {
    global $config;
    $msg="";
    $cabinetArray=array();
    // get Cabinet Size
    $ldap = $config->get_ldap_link();
    $ldap->cd($cabinet_dn);

    // get cabinet size
    $ldap->search('(objectClass=fdDcimCabinet)', ['fdDcimCabinetSize']);
    while ($cabinet = $ldap->fetch()) {
      $cabinetSize=$cabinet['fdDcimCabinetSize'][0];
    }
    
    // initialize empty cabinet
    for($i=$cabinetSize;$i>0;$i--){
      $cabinetArray[$i] = "empty";
    }

    // insert all component already declared in this cabinet
    $ldap->cd($config->current['BASE']);
    $ldap->search('(&(objectClass=fdDcimComponent)(fdDcimComponentCabinetId='.$cabinet_dn.'))', ['fdDcimComponentPosition','cn','fdDcimComponentSize']);
    while ($component = $ldap->fetch()) {
      $cName=$component['cn'][0];
      $cSize=$component['fdDcimComponentSize'][0];
      $cPosition=$component['fdDcimComponentPosition'][0];
     
      if ( $cSize + $cPosition -1 < $cabinetSize){
        $i = 0;
          while ( $i < $cSize){
          $cabinetArray[$cPosition + $i] = $cName;
          $i++;
        }
      }
    }
    return($cabinetArray);
  }
  
  // check if actual component position an d size are coherent
  public function checkCabinet($cabinetArray,$position, $size) : string
  {
    $i=0;
    while($i <= $size){
      if ($cabinetArray[$position + $i] != "empty" && $cabinetArray[$position + $i] != $this->attrs['cn'][0]){
        return(sprintf(_("Current position of component \"%s\" in cabinet conflict with \"%s\""),$this->attrs['cn'][0],$cabinetArray[$position + $i]));
      }
      $i++;
    }
    return("");

  }



  public function prepare_save (): array
  {
    global $config;
    
      if (empty($currentCabinet)){
        $msg=_("Cabinet must be set");
      }else{
        $currentSize=$this->attributesAccess['fdDcimComponentSize']->getValue();
        $currentPosition=$this->attributesAccess['fdDcimComponentPosition']->getValue();
        $msg=$this->checkCabinet($this->cabinetContent($currentCabinet),$currentPosition,$currentSize);
      }
      if ( ! empty($msg) ){
        $error = new FusionDirectoryError(
         htmlescape($msg)
        );
        $error->display();
        }
    return parent::prepare_save();

  }

}
