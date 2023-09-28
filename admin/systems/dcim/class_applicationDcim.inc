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



class applicationDcim extends simplePlugin
{

  protected $displayHeader  = TRUE;
  protected $loaded = FALSE;
  
  static function plInfo (): array
  {
    return [
      'plShortName'   => _('DCIM Application'),
      'plDescription' => _('DCIM Application'),
      'plPriority'    => 30,
      'plObjectClass' => ['fdDcimApplication'],
      'plObjectType'  => ['application','webapplication'],
      'plProvidedAcls'  => parent::generatePlProvidedAcls(static::getAttributesInfo())
    ];
  }



  static function getAttributesInfo (): array
  {
    global $config;

    $referential=explode($config->get_cfg_value('TaxonomySeparator'),$config->get_cfg_value('DcimApplicationInstanceRef'));


    return [

      'dcimApplicationProperties' => [
        'name'  => _('Application properties'),
        'attrs' => [

          new UsersAttribute(
            _('Technical contacts'), _('Technical contacts for this application '),
              'fdDcimApplicationTechnicalContactDn', FALSE),
          new UsersAttribute(
            _('Business contacts'), _('Business contacts for this application '),
              'fdDcimApplicationBusinessContactDn', FALSE),
          new stringAttribute(
              _('Description of Application'), _('Type of Location'),
               'fdDcimApplicationDescription', TRUE,''),
          ],
        ],
        'dcimApplicationDependancies' => [
          'name'  => _('Links definition'),
          //'class' => ['fullwidth'],
          'attrs' => [
          new OrderedArrayAttribute(
            new CharSeparatedCompositeAttribute(
              _("Dependancies"),
              'fdDcimApplicationDependancies',
                [
                  new TaxonomySelectAttribute(
                    _('Instance'), _('Instance of component'),
                    'fdDcimAppInstance', FALSE, '',$referential[0], $referential[1]
                  ),
                  new ObjectSelectAttribute(
                    _('Component A'), _('Component A'),
                    'fdDcimAppComponent', FALSE,
                    ['Server','application']),
                  new StringAttribute (_('Indications'),    _('Indications'), 'Indications'),
                ],
              ';',
              '',
              ''
              //_('Interface Design'),
              
            ),
            FALSE,[],TRUE),]
        ],
    ];
  }
}

