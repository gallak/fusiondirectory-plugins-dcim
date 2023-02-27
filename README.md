# fusiondirectory-plugins-dcim

This is a plugin for FusionDirectory that add some informations about Datacenter Informatio Management
It provide Building > room > rack component
It's based  on taxonomy plugins

## Why this plugin ?

It was designed to be a small tool for managing several kinf of asset.
It could be enhanced with several external tool ( i.e : start / stop sequence based on nut or script on virtual management system)

## fusiondirectory-plugins-dcim

FusionDirectory could be used for managing a lot of component such physical sevrer, network component. It a great solution for a simpel asset management.
By the way it could useful to have a more hierarchical view before management compoment.
This is the goal of DCIM ( as Data Center Information Management).
It allow to create :
  - Datacenter information
  - Zone ( subpart of a datacenter)
  - Rack ( subpart of Zone)

For each level, there is specific information like :
  - For Datacenter and Zone :
    - manager
    - physical Address
    - electrical and colling information
  - For Rack
    - size of rack 
  - For each system, a tab DCIM is avalaible which following information :
    - start/stop sequence in case of a full Shutdown
    - if it's a physical device :
      - physical place inside a rack
      - width ( in Rack unit)
    - if it's a virtual device
      - server management (such vcenter for vmware)

## How to install

`cd /usr/local/src/
git https://github.com/gallak/fusiondirectory-plugins-dcim.git
mv fusiondirectory-plugins-dcim dcim`

### Installation of ldap schema

`ldap-schema-manager -i ./dcim/contrib/schema/dcim-fd.schema`
`ldap-schema-manager -i ./dcim/contrib/schema/dcim.schema`

### Installation of plugin

```
fusiondirectory-plugin-manager --set-fd_home=/usr/local/share/fusiondirectory  --plugin-name=dcim --plugins-archive=/usr/local/src/gallak --install-plugin
Setting fd_home to /usr/local/share/fusiondirectory
plugin dcim will be used
Plugins folder /usr/local/src/gallak will be used
Installing FusionDirectory's plugins
Installing plugin dcim
Plugin record exist : cn=dcim,ou=plugins,ou=fusiondirectory,dc=demo,dc=fusion
Deleting it !
Create plugin record
Scanning and update Class.cache and translations
```

### usage

  - Go toi the DCIM entry
![Go to Dcim Menu](/docs/dcim.png "Dcim menu")
  - Detail of a Datacenter
![example of a datacenter](/docs/details-datacenter.png "Details of Datacenter")
  - Detail of a zone inside the Datacenter
![example of a zone](/docs/dc-zone-rack.png "Details of zone")
  - Detail of a cabinet inside a zone
![example of a rack](/docs/details-component.png "Details of a Rack")
  - Detail for a component
![example of a component](/docs/component.png "Details of a component")
For each component, you could provide information (position, size, ...)




## Simple Roadmap

It depens of you, but in order to have a complet DCIM and a centralized CMDB (Configuration Management Data Base)
We could imaginate a simple call to dedicated plateform in order to get main information for each type of component
Simple example :
  - network component : call [Netdisco](https://netdisco.org/) API
  - worsktation : call to [GLPI](https://glpi-project.org) or [OPSI](https://opsi.org) API
  - Virtual server : call to [VMware](https://www.vmware.com) or [Proxmox](https://pve.proxmox.org)
  - physical Server : call to direct management Card ( ILO / IdRac)

All those informations should be available trough FusionDirectory API and (hopefully) in a common Format
    
