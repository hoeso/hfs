# Creating a pure Entity

## Explanation 

- The Cloud Business Suite is all about entities and their relations to each other. As our first project we will be creating a system a country could use to organize the testing and vaccination process for the new Coronavirus.
- The first thing we will do is create a pure entity.

## Step 1: Create a table in the database for the entity:
```
mariadb -uroot -p
USE sarscov2t;
CREATE TABLE `Station` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Station` varchar(255) DEFAULT NULL,
  `TLD` enum('ar') NOT NULL DEFAULT 'ar',
  PRIMARY KEY (`ID`),
  UNIQUE KEY `IDX` (`Station`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8; 
```

## Step 2: Add a navigation item in the sidebar using naviStation.html:
```
nano ~/public_html/naviStation.html

```
Insert the following lines
```
<ul>
<li>
<a href="<?php echo $candyURL['Station']?>">Station</a>
</li>
</ul>
```
## Step 3: Add a navigation item in continueHere.prj:

```
nano ~/public_html/continueHere.prj
```
Insert the following line under`_eCandy = array(`:
```
"Station"=>"0",

```
And insert the following line under `$candyURL = array(`:
```
"Station"=>"mn.php?mn=pe&a=Station&u=Test-Location",
```

## Step 4: Since we created the table using an "enum" field, we need to declare it in our select.prj as well:


```
nano ~/public_html/select.prj
```
Insert the following lines under `$enumListe=array (`:
```
 "Station"=>"ar",// tld
```

We should now be able to see the newly created entity and menu item in our browser at [http://localhost/~hfs/](http://localhost/~hfs/)
