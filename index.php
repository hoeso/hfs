<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN"
"http://www.w3.org/TR/html4/DTD/strict.dtd">
<html>
<head>
<meta http-equiv="content-type" content="text/html;charset=utf-8">
<title>Flex Business Suite</title>
<script language=javascript type='text/javascript'>
  if( top.location != self.location )
  {
    top.location = self.location
  }
</script>
<link rel="stylesheet" href="./erica.css" media="screen" title="erica Stylesheet" />
</head>
<?php
if( 0 )
{   
  // fuer eine Inbetriebnahme bzw. Erstinstallation:
  // ist php ueberhaupt in Betrieb?
  $_E['wZu']="inBetriebnehmend";
  include("forkZu.inc");
  ?>
  <h4>Der PHP-Interpreter scheint nicht aufgerufen zu werden?</h4>
  <ol>
    <li>Ist das Paket <em>libapache2-mod-php5</em> installiert?
    <li>Ist PHP im mods-enabled/php5.conf freigegeben?
  </ol>
  <?php
}
$_E['bodyClass'] = "main";
$_E['bodyId'] = "main";
?>
<body class="<?php
echo $_E['bodyClass'];
?>" id="<?php
echo $_E['bodyId'];
?>">
<?php include("kopfteil.html"); ?>
<?php include("kopfteil.prj"); ?>
<?php include("naviSymbols.prj"); ?>
<?php include("endeContainer.html"); ?>
<?php include("hauptteil.html"); ?>
<?php include("haupttext.html"); ?>
<?php include("endeContainer.html"); ?>
<?php include("seitenleiste.html"); ?>
<?php include("hauptnavigation.html"); ?>
<?php //include("naviGoogle.html"); ?>
<?php //include("naviElemente.html"); ?>
<?php //include("naviEDV.sql"); ?>
<?php //include("naviUpload.html"); ?>
<?php include("naviCFS.html"); ?>
<?php include("endeNavigation.html"); ?>
<?php include("endeContainer.html"); ?>
<?php include("endeContainer.html");//hauptteil ?>
</body>
</html>
