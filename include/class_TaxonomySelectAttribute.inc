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



class TaxonomySelectAttribute extends SelectAttribute
 {


  function __construct ($label, $description, $ldapName, $required = TRUE, $acl = "", $referential, $taxonomy)
  {
    $this->referential=$referential;
    $this->taxonomy=$taxonomy;
    parent::__construct($label, $description, $ldapName, $required, [], "", NULL, $acl, $referential, $taxonomy);

  }

   public function getAllTerms()
     {
     global $config;
     $ldap = $config->get_ldap_link();
    
     $allTerms=array();
     $ldap->cd($config->current['BASE']);
     $ldap->search('(&(objectClass=fdTaxonomyTerms)(fdTaxonomyReferentiel='.$this->referential.")(fdTaxonomyName=".$this->taxonomy.'))', ['fdTaxonomyTermCode','fdTaxonomyTermLongLabel']);
     while ($term = $ldap->fetch()) {
         $allTerms[$term['fdTaxonomyTermCode'][0]]= array( 'term' => $term['fdTaxonomyTermCode'][0],
                                        'description' => $term['fdTaxonomyTermLongLabel'][0],
                                         );
         }
     return($allTerms);
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
         $termsId    = [];
         $termsDescription = [];
         foreach ($this->getAllTerms() as $name => $content){
             $termsDescription[] = $content['description'];
             $termsId[] =  $content['term'];
         }
     $this->setChoices($termsId, $termsDescription);
     }
 
 }
 