<fieldset id="{$sectionId}" class="plugin-section{$sectionClasses}">
  <legend><span>{if !empty($sectionIcon)}<img src="{$sectionIcon|escape}" alt=""/>{/if}{$section|escape}</span></legend>
  <div>
  <table>
  
  {if $locationType == "virtual"}
    <tr class="
      subattribute
      {if !$attributes.fdDcimVirtualManagementServerDn.readable}nonreadable{/if}
      {if !$attributes.fdDcimVirtualManagementServerDn.writable}nonwritable{/if}
    ">
      <td title="{$attributes.fdDcimVirtualManagementServerDn.description|escape}">
        <label for="{$attributes.fdDcimVirtualManagementServerDn.htmlid}">
          {eval var=$attributes.fdDcimVirtualManagementServerDn.label}
        </label>
      </td>
      <td>{eval var=$attributes.fdDcimVirtualManagementServerDn.input}</td>
    </tr>   

  {else}
    <!-- common cabinet and zone -->
    <tr class="
      subattribute
      {if !$attributes.fdDcimComponentFrontImage.readable}nonreadable{/if}
      {if !$attributes.fdDcimComponentFrontImage.writable}nonwritable{/if}
    ">
      <td title="{$attributes.fdDcimComponentFrontImage.description|escape}">
        <label for="{$attributes.fdDcimComponentFrontImage.htmlid}">
          {eval var=$attributes.fdDcimComponentFrontImage.label}
        </label>
      </td>
      <td>{eval var=$attributes.fdDcimComponentFrontImage.input}</td>
    </tr>

    <tr class="
      subattribute
      {if !$attributes.fdDcimComponentRearImage.readable}nonreadable{/if}
      {if !$attributes.fdDcimComponentRearImage.writable}nonwritable{/if}
    ">
      <td title="{$attributes.fdDcimComponentRearImage.description|escape}">
        <label for="{$attributes.fdDcimComponentRearImage.htmlid}">
          {eval var=$attributes.fdDcimComponentRearImage.label}
        </label>
      </td>
      <td>{eval var=$attributes.fdDcimComponentRearImage.input}</td>
    </tr>

  
    {if $locationType == "cabinet"}
      <tr class="
        subattribute
        {if !$attributes.fdDcimComponentCabinetDn.readable}nonreadable{/if}
        {if !$attributes.fdDcimComponentCabinetDn.writable}nonwritable{/if}
        ">
        <td title="{$attributes.fdDcimComponentCabinetDn.description|escape}">
            <label for="{$attributes.fdDcimComponentCabinetDn.htmlid}">
             {eval var=$attributes.fdDcimComponentCabinetDn.label}
            </label>
        </td>
        <td>{eval var=$attributes.fdDcimComponentCabinetDn.input}</td>
      </tr>
      <tr class="
        subattribute
        {if !$attributes.fdDcimComponentSize.readable}nonreadable{/if}
        {if !$attributes.fdDcimComponentSize.writable}nonwritable{/if}
        ">
        <td title="{$attributes.fdDcimComponentSize.description|escape}">
          <label for="{$attributes.fdDcimComponentSize.htmlid}">
          {eval var=$attributes.fdDcimComponentSize.label}
          </label>
        </td>
      <td>{eval var=$attributes.fdDcimComponentSize.input}</td>
      </tr>
      <tr class="
        subattribute
        {if !$attributes.fdDcimComponentPosition.readable}nonreadable{/if}
        {if !$attributes.fdDcimComponentPosition.writable}nonwritable{/if}
        ">
        <td title="{$attributes.fdDcimComponentPosition.description|escape}">
          <label for="{$attributes.fdDcimComponentPosition.htmlid}">
            {eval var=$attributes.fdDcimComponentPosition.label}
          </label>
        </td>
        <td>{eval var=$attributes.fdDcimComponentPosition.input}</td>
      </tr>    
    {elseif $locationType =="zone"}
      <tr class="
        subattribute
        {if !$attributes.fdDcimComponentZoneDn.readable}nonreadable{/if}
        {if !$attributes.fdDcimComponentZoneDn.writable}nonwritable{/if}
        ">
        <td title="{$attributes.fdDcimComponentZoneDn.description|escape}">
          <label for="{$attributes.fdDcimComponentZoneDn.htmlid}">
            {eval var=$attributes.fdDcimComponentZoneDn.label}
          </label>
        </td>
        <td>{eval var=$attributes.fdDcimComponentZoneDn.input}</td>
      </tr>
      {/if}
    {/if}

  </table>
  </div>
</fieldset>
