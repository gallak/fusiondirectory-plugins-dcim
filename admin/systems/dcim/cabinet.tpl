<div id="{$sectionId}" class="plugin-section{$sectionClasses}">
  <span class="legend">
    {if $sectionIcon}<img src="{$sectionIcon|escape}" alt="" />{/if}{$section|escape}
  </span>
  <div >
    <table style="border: 2px solid black;">
      {assign var=rackIndice value=$attributes.fdDcimCabinetSize_bis}
      {assign var=componentSize value=0}
      {assign var=count value=0}
      <thead style="border: 1px solid black;text-align: center;">
        <tr >
          <td style="border: 1px solid black;height:20px; width:40px;">{t}Position{/t}</td>
          <td style="border: 1px solid black;width:200px; ">{t}Front{/t}</td>
          <td style="border: 1px solid black;width:200px; ">{t}Rear{/t}</td>
          <td style="border: 1px solid black;height:20px; width:40px">{t}Position{/t}</td>
        </tr>
      </thead>
      <tbody style="border: 1px solid black;text-align: center;">
        {while $rackIndice > 0}
          <tr style="border:1px solid black;">
            <td style="border: 1px solid black;height:18px; width:40px">U{$rackIndice}</td>
            {if isset($attributes.fdDcimCabinetDesign[$rackIndice])}
              {$componentSize = $attributes.fdDcimCabinetDesign[$rackIndice]['size']}
              
                {if ! empty($attributes.fdDcimCabinetDesign[$rackIndice]['imageFront'])}
                  <td style="border: 1px solid black;width: 200px;" rowspan={$componentSize}>
                  <a href={$attributes.fdDcimCabinetDesign[$rackIndice]['link']}><img src="data:image/jpeg;base64,{$attributes.fdDcimCabinetDesign[$rackIndice]['imageFront']}"
                    title="{$attributes.fdDcimCabinetDesign[$rackIndice]['name']} - {$attributes.fdDcimCabinetDesign[$rackIndice]['description']} - {$attributes.fdDcimCabinetDesign[$rackIndice]['size']}" /></a>
                {else}
                  <td style="border: 1px solid black;width:200px" rowspan={$componentSize}>
                  <a href={$attributes.fdDcimCabinetDesign[$rackIndice]['link']}>{$attributes.fdDcimCabinetDesign[$rackIndice]['description']}</a>
                {/if}
              </td>

              {if ! empty($attributes.fdDcimCabinetDesign[$rackIndice]['imageRear'])}
                <td style="border: 1px solid black;width:200px;" rowspan={$componentSize}>
                <a href={$attributes.fdDcimCabinetDesign[$rackIndice]['link']}><img src="data:image/jpeg;base64,{$attributes.fdDcimCabinetDesign[$rackIndice]['imageRear']}"
                  title="{$attributes.fdDcimCabinetDesign[$rackIndice]['name']} - {$attributes.fdDcimCabinetDesign[$rackIndice]['description']} - {$attributes.fdDcimCabinetDesign[$rackIndice]['size']}" /></a>
              {else}
                <td style="border: 1px solid black;width:200px;" rowspan={$componentSize}>
                <a href={$attributes.fdDcimCabinetDesign[$rackIndice]['link']}>{t}Rear of{/t} {$attributes.fdDcimCabinetDesign[$rackIndice]['description']}</a>
              {/if}
              </td>
            {else}
              {if $count >= $componentSize}
                <td style="border: 1px solid black;">{t}Empty location{/t}</td>
                <td style="border: 1px solid black;">{t}Empty location{/t}</td>
                {$count = 0}
                {$componentSize=0}
              {/if}
              {$count = $count +1 }
            {/if}
            <td style="border: 1px solid black;height:18px; width:40px;">U{$rackIndice}</td>
            {$rackIndice = $rackIndice - 1}
          </tr>
        {/while}
      </tbody>
    </table>
  </div>
</div>