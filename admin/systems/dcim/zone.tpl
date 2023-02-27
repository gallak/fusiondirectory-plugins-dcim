<div id="{$sectionId}" class="plugin-section{$sectionClasses}">
  <span class="legend">
    {if $sectionIcon}<img src="{$sectionIcon|escape}" alt="" />{/if}{$section|escape}
  </span>
  <div>

  {foreach from=$attributes.fdDcimZoneDesign key=type item=content}
    <h1>{t}{$type}{/t}</h1>
    <ul>
    {foreach from=$content item=element}
        <li> <a href={$element.link}>{$element.name} - {$element.description}</a></li>
    {/foreach}
    </ul>
  {/foreach}
 
  </div>