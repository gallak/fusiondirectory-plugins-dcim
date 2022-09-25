# fusiondirectory-plugins-dcim

This is a plugin for FusionDirectory that add some informations about Datacenter Informatio Management
It provide Datacenter > zone > cabinet
It's based  on taxonomy plugins

## Why this plugin ?

It was designed to be a small tool for managing simple "datacenter" 

## Todo

every thing
WORK In Progress

## How to install

`git https://github.com/gallak/fusiondirectory-plugins-dcim.git
mv fusiondirectory-plugins-dcim dcim`

### Installation of ldap schema

`ldap-schema-manager -i ./dcim/contrib/schema/dcim-fd.schema`
`ldap-schema-manager -i ./dcim/contrib/schema/dcim.schema`

### Installation of plugin

```fusiondirectory-setup --set-fd_home=/usr/local/share/fusiondirectory --install-plugins
Setting fd_home to /usr/share/fusiondirectory
Installing FusionDirectory's plugins
Where is your plugins archive or folder?:
<complete current path>            
Available plugins:
1:dcim

fusiondirectory-setup --update-cache --update-locales
```

### usage



