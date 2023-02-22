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
  
  public $locationsArray=['cabinet' => 'fdDcimComponentCabinetDn','zone' => 'fdDcimComponentZoneDn','virtual' => 'fdDcimVirtualManagementServer'];

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
            _('Location'), _('Type of Location'),
             'fdDcimFakeLocation', TRUE,[],'',[]),
          new IntAttribute(
            _('Start sequence'), _('Start sequence'),
              'fdDcimComponentStartSequence', FALSE,0,10,0),
          new IntAttribute(
            _('Stop sequence'), _('Stop sequence'),
              'fdDcimComponentStopSequence', FALSE,0,10,0),
          new UsersAttribute(
            _('Responsables'), _('Responsables of Component'),
              'fdDcimComponentManagerDn', FALSE),
        ],
      ],

      'DedicatedComponent' => [
        'name'  => _('Physical component'),
        'attrs' => [ 
            new dcimCabinetSelectAttribute(
                  _('Cabinet name'), _('Cabinet Name'),
                  'fdDcimComponentCabinetDn', FALSE),
            new dcimZoneSelectAttribute(
                    _('Zone name'), _('Zone Name'),
                    'fdDcimComponentZoneDn', FALSE),
            new StringAttribute(
                  _('Size'), _('Size of the Component'),
                  'fdDcimComponentSize', FALSE,1),
            new StringAttribute(
                  _('Position'), _('Position of the Component'),
                  'fdDcimComponentPosition', FALSE,1),
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
        'template' => get_template_path('dcimComponent.tpl', TRUE, dirname(__FILE__)),
      ],
    ];
  }



  public function locationChanged(){
    $this->fdDcimFakeLocation=$this->attributesAccess['fdDcimFakeLocation']->getValue();
  }



  function __construct ($dn = NULL, $object = NULL, $parent = NULL, $mainTab = FALSE)
  {
    parent::__construct($dn, $object, $parent, $mainTab);
  
    $this->attributesAccess['fdDcimFakeLocation']->setInLdap(FALSE);
    $this->attributesAccess['fdDcimFakeLocation']->setChoices(array_keys($this->locationsArray));

    foreach ($this->locationsArray as $location => $field){
      if (! empty($this->$field)){
        $this->attributesAccess['fdDcimFakeLocation']->setValue($location);
      }
    }

    $this->locationChanged();
    $this->attributesAccess['fdDcimFakeLocation']->setSubmitForm('locationChanged');
  }

  public function render (): string
  {
    $smarty = get_smarty();
    $smarty->assign('locationType',$this->fdDcimFakeLocation);
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
    $ldap->search('(&(objectClass=fdDcimComponent)(fdDcimComponentCabinetDn='.$cabinet_dn.'))', ['fdDcimComponentPosition','cn','fdDcimComponentSize']);
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
    switch ($this->fdDcimFakeLocation) {
      case 'virtual':
        // empty field not necessary for virtual location
        $this->fdDcimComponentCabinetDn="";
        $this->fdDcimComponentZoneDn="";
        $this->fdDcimComponentSize="";
        $this->fdDcimComponentPosition="";
        $this->fdDcimComponentFrontImage="";
        $this->fdDcimComponentRearImage="";

        break;
      case 'cabinet':
        // empty field not necessary for cabinet location
        $this->fdDcimVirtualManagementServer="";
        break;

      case 'zone':
        // empty field not necessary for zone location
        $this->fdDcimComponentCabinetDn="";
        $this->fdDcimVirtualManagementServer="";
        $this->fdDcimComponentSize="";
        $this->fdDcimComponentPosition="";
  
        break;
     }
    return parent::prepare_save();
  }

}
