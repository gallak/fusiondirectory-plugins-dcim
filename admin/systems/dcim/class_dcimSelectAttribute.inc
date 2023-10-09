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


class dcimZoneSelectAttribute extends SelectAttribute
{
  public function getAllZones()
    {
    global $config;
    $ldap = $config->get_ldap_link();
    
    $allZones=array();
    $ldap->cd($config->current['BASE']);
    $ldap->search('(objectClass=fdDcimZone)', ['dn','fdDcimZoneDatacenterDn','cn','description']);
    while ($zone = $ldap->fetch()) {
        $dc=ldap_explode_dn($zone['fdDcimZoneDatacenterDn'][0],1)[0];
        $allZones[$zone['dn']]= array( 'zoneCn' => $dc." > ".$zone['cn'][0],
                                       'zoneDescription' => $zone['description'][0],
                                        );
        }
    return($allZones);
  }


    function setParent (&$plugin)
    {
        parent::setParent($plugin);
        if (is_object($this->plugin)) {
            $this->updateChoices();
        }
    }

    function updateChoices ()
    {
        global $config;
        $zonesDn    = [];
        $zonesDescription = [];
        foreach ($this->getAllZones() as $name => $content){
            $zonesDescription[] = $content['zoneCn']." (".$content['zoneDescription'].")";
            $zonesDn[] = $name;
        }
    $this->setChoices($zonesDn, $zonesDescription);
    }

}

class dcimCabinetSelectAttribute extends SelectAttribute
{
  public function getAllCabinets()
    {
    global $config;
    $ldap = $config->get_ldap_link();
    $ldap_bis = $config->get_ldap_link();
    $ldap->cd($config->current['BASE']);

    
    $allCabinets=array();
    $ldap->search('(objectClass=fdDcimCabinet)', ['dn','fdDcimCabinetZoneDn','cn','description']);
    while ($cabinet = $ldap->fetch()) {

        
        $ldap_bis->cd($cabinet['fdDcimCabinetZoneDn'][0]);
    
        $ldap_bis->search('(objectClass=fdDcimZone)', ['fdDcimZoneDatacenterDn','cn']);

        while ($record = $ldap_bis->fetch()) {
            $zone=$record['cn'][0];
            $dc=ldap_explode_dn($record['fdDcimZoneDatacenterDn'][0],1)[0];    

        $allCabinets[$cabinet['dn']]= array('cabinetCn' => $dc." > ".$zone." > ".$cabinet['cn'][0],
                                       'cabinetDescription' => $cabinet['description'][0],
                                        );
                                    }
        }

    return($allCabinets);
  }


    function setParent (&$plugin)
    {
        parent::setParent($plugin);
        if (is_object($this->plugin)) {
            $this->updateChoices();
        }
    }

    function updateChoices ()
    {
        global $config;
        $cabinetsDn    = [];
        $cabinetsDescription = [];
        foreach ($this->getAllCabinets() as $name => $content){
            $cabinetsDescription[] = $content['cabinetCn']." (".$content['cabinetDescription'].")";
            $cabinetsDn[] = $name;
        }
    $this->setChoices($cabinetsDn, $cabinetsDescription);
    }

}


class dcimLinksSelectAttribute extends SelectAttribute
{
  public function getAllLinks()
    {

    global $config;
    $allLinks=array();
    foreach (array_filter($this->choices) as $element) {
        
        $ldap = $config->get_ldap_link(); 
        $ldap->search('(objectClass='.$element.')', ['dn','cn','description']);
        while ($item = $ldap->fetch()) {
            $allLinks[$item['dn']]= array('LinksCn' => $item['cn'][0],
                                          'LinksDescription' => $item['description'][0],
                                            );
                                        }
        }




    //$ldapNet = $config->get_ldap_link();
    //$ldapSrv = $config->get_ldap_link();
    //$ldapNet->cd($config->current['BASE']);
    //$ldapSrv->cd($config->current['BASE']);

    
    
    //$ldapNet->search('(objectClass=fdIpamSubnet)', ['dn','cn','description']);
    //$ldapSrv->search('(objectClass=fdServer)', ['dn','cn','description']);

    //while ($item = $ldapNet->fetch()) {
    //    $allLinks[$item['dn']]= array('LinksCn' => "NET  > ".$item['cn'][0],
    //                                  'LinksDescription' => $item['description'][0],
    //                                    );
    //                                }
        

    //while ($item = $ldapSrv->fetch()) {
    //    $allLinks[$item['dn']]= array('LinksCn' => "SERV  > ".$item['cn'][0],
    //                                  'LinksDescription' => $item['description'][0],
    //                                   );
    //                                }
        
    //var_dump($allLinks);
    return($allLinks);
  }


    function setParent (&$plugin)
    {
        parent::setParent($plugin);
        if (is_object($this->plugin)) {
            $this->updateChoices();
        }
    }

    function updateChoices ()
    {
        global $config;
        $linksDn    = [];
        $linksDescription = [];
        foreach ($this->getAllLinks() as $name => $content){
            $linksDescription[] = $content['LinksCn']." (".$content['LinksDescription'].")";
            $linksDn[] = $name;
          
        }
    $this->setChoices($linksDn, $linksDescription);
    }

}