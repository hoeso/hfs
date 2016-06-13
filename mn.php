<?php
function dEcho( $file, $str )
{
  if( !isset($_REQUEST['d']) )
    return;
  echo"\n" . $file . " -- $str<br>\n";
}
if( isset($_REQUEST['d']) )
{
  $a_ = explode( "/", __file__ );
  $b_ = $a_[count($a_)-1];
  echo"\n" . $b_ . " -- POSTS:<br>";
  foreach( $_POST as $k=>$elem )
    echo"\nk : $k, elem: $elem<br>";
  echo"\n" . $b_ . " -- REQUESTS:<br>";
  foreach( $_REQUEST as $k=>$elem )
    echo"\nk : $k, elem: $elem<br>";
  if( 0/*isset($_FILES)*/ )
  {
    echo"\nFILES:<br>";
    foreach( $_FILES as $k=>$elem )
      echo"\nk : $k, elem: $elem<br>";
  }
}
function logModul( $str )
{
  echo"\n<!-- Modul $str: -->\n";
}
function logForkedModul( $str )
{
  echo"\n<!-- Modul $str: -->\n";
}
global $_E;
$_E['mn'] = $_REQUEST["mn"];
$_E['bodyClass'] = "main";
$_E['bodyId'] = "main";
$exitus="you don't exist. Go away!";
include("mn.prj");
include("tee.inc");
?>
<!DOCTYPE html>
<html>
<head>
<title><?php
if( isset($_REQUEST['u']) )
  echo $_REQUEST['u'];
else
{?>
CFS<?php
}?>
</title>
<meta http-equiv="content-type" content="text/html;charset=utf-8">
<link rel="stylesheet" href="./fcs.css" media="screen" title="Flex Care Suite-Stylesheet" />
</head>
<body class="<?php
echo $_E['bodyClass'];
?>" id="<?php
echo $_E['bodyId'];
?>"><?php
function logZustandswechsel( $str )
{
  echo"\n<!-- Eintreten in Zustand $str ... -->\n";
}

if( isset($_E['wZu']) )
  logZustandswechsel($_E['wZu']);
else if( isset($wZu) )
  logZustandswechsel($wZu);
else
  logZustandswechsel('kein Zustand gesetzt?!');
include("wZu.inc");
?>
