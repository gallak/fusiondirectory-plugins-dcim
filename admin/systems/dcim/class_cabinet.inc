<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)
  Copyright (C) 2016-2017  FusionDirectory
  Copyright (C) 2021  Antoine Gallavardin

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



class cabinet extends simplePlugin
{

  protected $displayHeader  = TRUE;
  protected $loaded = FALSE;

  static function plInfo (): array
  {
    return [
      'plShortName'   => _('cabinet'),
      'plDescription' => _('cabinet'),
      'plObjectClass' => ['fdDcimCabinet'],
      'plObjectType'  => ['cabinet' => [
        'name'        => _('cabinet'),
        'icon'        => 'geticon.php?context=applications&icon=cabinet&size=16',
        'ou'          => get_ou('DcimCabinetRDN'),
        'mainAttr'    => 'cn',
      ]],
      'plSearchAttrs'  => ['description'],
      'plProvidedAcls'  => parent::generatePlProvidedAcls(static::getAttributesInfo())
    ];
  }


  private function getClassIndex( $className){
    return(pluglist::pluginInfos('systemManagement')['INDEX']);

  } 


  function getCabinetContent (): array
  {
    global $config;
    $ldap = $config->get_ldap_link();
    $allComponents = array();
    $ldap->search('(&(objectClass=fdDcimComponent)(fdDcimComponentCabinetId='.$this->dn.'))', ['fdDcimComponentPosition','cn','description','fdDcimComponentSize','fdDcimComponentRearImage','fdDcimComponentFrontImage','dn']);
    while ($component = $ldap->fetch()) {
        // -1 is necessary,  position are inversed
        $allComponents[$component['fdDcimComponentPosition'][0] -1 + $component['fdDcimComponentSize'][0]]= array(
                                'position' => $component['fdDcimComponentPosition'][0],
                                'size' => $component['fdDcimComponentSize'][0],
                                'description' => $component['description'][0],
                                'name' => $component['cn'][0],
                                'imageRear' => base64_encode($component['fdDcimComponentRearImage'][0]),
                                'imageFront' => base64_encode($component['fdDcimComponentFrontImage'][0]),
                                'link' => htmlspecialchars('main.php?plug='.$this->getClassIndex('systemManagement').'&reset=1&act=listing_edit&dn='.$component['dn'])
                              );
    }

    return($allComponents);
  } 



  static function getAttributesInfo (): array
  {
    return [
      'cabinetInfo' => [
        'name'  => _('cabinet Information'),
        'attrs' => [
                new BaseSelectorAttribute(get_ou('DcimZoneRDN')),
                new StringAttribute(
                  _('cabinet'), _('cabinet'),
                  'cn', TRUE),
                new StringAttribute(
                  _('Description'), _('Description'),
                  'description', TRUE),
                new IntAttribute(
                  _('Size'), _('Size of the Cabinet'),
                  'fdDcimCabinetSize', TRUE,0,42,42),
                 new dcimZoneSelectAttribute(
                  _('Zone'), _('Zone'),
                  'fdDcimCabinetZone', TRUE,
                ),
                ]
      ],
      'content' => [
        'name'  => _('Content of Cabinet'),
        'attrs' => [
            new FakeAttribute('fdDcimCabinetDesign'),
            new FakeAttribute('fdDcimCabinetSize_bis'),
            ],
          'template' => get_template_path('cabinet.tpl', TRUE, dirname(__FILE__)),
          ],
    ];
  }

  function __construct ($dn = NULL, $object = NULL, $parent = NULL, $mainTab = FALSE)
  {
    global $config;
    parent::__construct($dn, $object, $parent, $mainTab);
    $smarty = get_smarty();
    $this->fdDcimCabinetDesign=$this->getCabinetContent();
    $this->fdDcimCabinetSize_bis=$this->fdDcimCabinetSize;

  }
} 
