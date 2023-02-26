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



class zone extends simplePlugin
{

  protected $displayHeader  = TRUE;
  protected $loaded = FALSE;

  static function plInfo (): array
  {
    return [
      'plShortName'   => _('zone'),
      'plDescription' => _('zone'),
      'plObjectClass' => ['fdDcimZone'],
      'plObjectType'  => ['zone' => [
        'name'        => _('zone'),
        'icon'        => 'geticon.php?context=applications&icon=zone&size=16',
        'ou'          => get_ou('DcimZoneRDN'),
        'mainAttr'    => 'cn',
      ]],
      'plSearchAttrs'  => ['description','fdDcimZoneDatacenterDn'],

      'plProvidedAcls'  => parent::generatePlProvidedAcls(static::getAttributesInfo())
    ];
  }

  private function getClassIndex( $className){
    return(pluglist::pluginInfos($className)['INDEX']);

  } 
  function getZoneContent (): array
  {
    global $config;
    $ldap = $config->get_ldap_link();
    $allElements = array();
    $ldap->search('(|(fdDcimComponentZoneDn='.$this->dn.')(fdDcimCabinetZoneDn='.$this->dn.'))',
     ['cn','description','dn','objectClass']);
     
    while ($element = $ldap->fetch()) {
        // -1 is necessary,  position are inversed
        if (in_array('fdServer',$element['objectClass'])){
          $link=htmlspecialchars('main.php?plug='.$this->getClassIndex('systemManagement').'&reset=1&act=listing_edit&dn='.$element['dn']);
        }elseif(in_array('fdServer',$element['objectClass'])){
          $link=htmlspecialchars('main.php?plug='.$this->getClassIndex('dcimManagement').'&reset=1&act=listing_edit&dn='.$element['dn']);
        }
        $allElements[$element['dn']] = array(
                                'description' => $element['description'][0],
                                'name' => $element['cn'][0],
                                'link' => $link
                              );
    }
    var_dump($allElements);
    return($allElements);
  }

  static function getAttributesInfo (): array
  {
    return [
      'zone' => [
        'name'  => _('zone'),
        'class' => ['fullwidth'],
        'attrs' => [
                new BaseSelectorAttribute(get_ou('DcimZoneRDN')),
                new StringAttribute(
                  _('Name'), _('Zone Name'),
                  'cn', TRUE),
                new StringAttribute(
                  _('Description'), _('Description Zone'),
                  'description', TRUE),
                new UsersAttribute(
                  _('Authorized Person'), _('Authorized Person'),
                  'fdDcimZoneAuthorizedPersonDn', FALSE),
                new ObjectSelectAttribute(
                  _('Datacenter'), _('Datacenter'),
                  'fdDcimZoneDatacenterDn', TRUE,
                  ['datacenter']),
                ]
        ],
      'content' => [
        'name'  => _('Content of Zone'),
        'class' => ['fullwidth'],
        'attrs' => [
          new FakeAttribute('fdDcimZoneDesign'),
          ],
        'template' => get_template_path('zone.tpl', TRUE, dirname(__FILE__)),
        ],
    ];
  }
 
  function __construct ($dn = NULL, $object = NULL, $parent = NULL, $mainTab = FALSE)
  {
    global $config;
    parent::__construct($dn, $object, $parent, $mainTab);
    //$smarty = get_smarty();
    //$this->fdDcimCabinetDesign=$this->getCabinetContent();
    //$this->fdDcimCabinetSize_bis=$this->fdDcimCabinetSize;
    var_dump($this->getZoneContent());

  }

}
