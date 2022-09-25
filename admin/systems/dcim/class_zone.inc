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
        'ou'          => get_ou('fdDcimZoneRDN'),
        'mainAttr'    => 'cn',
      ]],
      'plSearchAttrs'  => ['description'],

      'plProvidedAcls'  => parent::generatePlProvidedAcls(static::getAttributesInfo())
    ];
  }

  static function getAttributesInfo (): array
  {
    return [
      'zone' => [
        'name'  => _('zone'),
        'class' => ['fullwidth'],
        'attrs' => [
                new StringAttribute(
                  _('Name'), _('Zone Name'),
                  'cn', TRUE),
                new StringAttribute(
                  _('Description'), _('Description Zone'),
                  'description', TRUE),
                new UsersAttribute(
                  _('Authorized Person'), _('Authorized Person'),
                  'fdDcimZoneAuthorizedPerson', TRUE),
                new ObjectSelectAttribute(
                  _('Datacenter'), _('Datacenter'),
                  'fdDcimZoneDatacenter', FALSE,
                  ['datacenter']),
                ]
      ]
    ];
  }
}
