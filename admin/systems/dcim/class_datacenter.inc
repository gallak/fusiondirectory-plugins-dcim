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


 
class datacenter extends simplePlugin
{

  protected $displayHeader  = TRUE;
  protected $loaded = FALSE;

  static function plInfo (): array
  {
    return [
      'plShortName'   => _('datacenter'),
      'plDescription' => _('datacenter'),
      'plObjectClass' => ['fdDcimDatacenter'],
      'plObjectType'  => ['datacenter' => [
        'name'        => _('datacenter'),
        'icon'        => 'geticon.php?context=applications&icon=datacenter&size=16',
        'ou'          => get_ou('DcimDatacenterRDN'),
        'mainAttr'    => 'cn',
      ]],
      'plSearchAttrs'  => ['description'],

      'plProvidedAcls'  => parent::generatePlProvidedAcls(static::getAttributesInfo())
    ];
  }

  static function getAttributesInfo (): array
  {
    return [
      'datacenterInfo' => [
        'name'  => _('Information'),
        'class' => ['fullwidth'],
        'attrs' => [
                new BaseSelectorAttribute(get_ou('DcimZoneRDN')),
                new StringAttribute(
                  _('Name'), _('Name of datacenter'),
                  'cn', TRUE),
                new StringAttribute(
                  _('Description'), _('Description of Datacenter'),
                  'description', TRUE),
                new UsersAttribute(
                  _('Responsables'), _('Responsables of Datacenter'),
                  'fdDcimDatacenterManagerDn', FALSE),
        ]
      ],
      'datacenterLocalization' => [
        'name'  => _('Localization'),
        'class' => ['fullwidth'],
        'attrs' => [
                new StringAttribute(
                  _('Location'), _('Location'),
                  'l', FALSE
                ),
                new StringAttribute(
                  _('State'), _('State'),
                  'st', FALSE
                ),
                new PostalAddressAttribute(
                  _('Address'), _('Business postal address'),
                  'postalAddress', FALSE
                ),
                new CompositeAttribute(
                  _('GPS Coordinate'),
                  'fdDcimDatacenterGPS',
                  [
                    new StringAttribute(_('GPS X'), _('Latitude'),'coord_X',FALSE),
                    new StringAttribute(_('GPS Y'), _('Longitude'),'coord_Y',FALSE),
                  ],
                  '/([0-9.-]*):([0-9.-]*)/',
                  '%s:%s',
                  )
        ]
      ],
      'datacenterTechnical' => [
        'name'  => _('Technical'),
        'class' => ['fullwidth'],
        'attrs' => [
                new StringAttribute(
                  _('Power'), _('Power Capacity (in Kw)'),
                  'fdDcimPowerCapacity',FALSE),
                new StringAttribute(
                  _('Cooling'), _('Cooling capacity (in Btu)'),
                  'fdDcimCoolingCapacity',FALSE),
        ] 
      ],
    ];
  }

}
