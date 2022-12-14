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
    $ldap->search('(objectClass=fdDcimZone)', ['dn','fdDcimZoneDatacenter','cn','description']);
    while ($zone = $ldap->fetch()) {
        $dc=ldap_explode_dn($zone['fdDcimZoneDatacenter'][0],1)[0];
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
    $ldap->search('(objectClass=fdDcimCabinet)', ['dn','fdDcimCabinetZone','cn','description']);
    while ($cabinet = $ldap->fetch()) {

        
        $ldap_bis->cd($cabinet['fdDcimCabinetZone'][0]);
    
        $ldap_bis->search('(objectClass=fdDcimZone)', ['fdDcimZoneDatacenter','cn']);

        while ($record = $ldap_bis->fetch()) {
            $zone=$record['cn'][0];
            $dc=ldap_explode_dn($record['fdDcimZoneDatacenter'][0],1)[0];    

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