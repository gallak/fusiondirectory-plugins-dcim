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


class componentZone extends simplePlugin
{

  protected $displayHeader  = TRUE;
  protected $loaded = FALSE;

  static function plInfo (): array
  {
    return [
      'plShortName'   => _('DCIM Component'),
      'plDescription' => _('DCIM Component'),
      'plPriority'    => 30,
      'plObjectClass' => ['fdDcimComponentZone'],
      'plObjectType'  => ['workstation','server','component'],
//=> [
//        'name'        => _('NetDisco'),
//        'icon'        => 'geticon.php?context=types&icon=ethernet&size=16',
//      ]],

      'plProvidedAcls'  => parent::generatePlProvidedAcls(static::getAttributesInfo())
    ];
  }



  static function getAttributesInfo (): array
  {
    return [
      'topology' => [
        'class' => ['fullwidth'],
        'name'  => _('Dcim component'),
        'attrs' => [
            new ObjectSelectAttribute(
                  _('Component'), _('Component'),
                  'fdDcimComponentZoneId', FALSE,
                  ['zone']),
            new IntAttribute(
                  _('Size'), _('Size of the Compnent'),
                  'fdDcimComponentZoneSize', TRUE,'',''),
            new IntAttribute(
                  _('Position'), _('Position of the Compnent'),
                  'fdDcimComponentZonePosition', TRUE,'',''),
        ],
      ],
    ];
  }


  function __construct ($dn = NULL, $object = NULL, $parent = NULL, $mainTab = FALSE)
  {
 
  parent::__construct($dn, $object, $parent, $mainTab);
  }


}
