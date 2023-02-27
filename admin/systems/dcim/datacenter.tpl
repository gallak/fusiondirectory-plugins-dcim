<div id="{$sectionId}" class="plugin-section{$sectionClasses}">
  <span class="legend">
    {if $sectionIcon}<img src="{$sectionIcon|escape}" alt="" />{/if}{$section|escape}
  </span>
  <div>

  {t}List of zone{/t}
    <ul>
    {foreach from=$attributes.fdDcimDatacenterDesign item=element}
        <li> <a href={$element.link}>{$element.name} - {$element.description}</a></li>
    {/foreach}
    </ul>

 
  </div>