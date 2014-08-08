<?php
if( 0 )
{
  echo"\nPOSTS:<br>";
  foreach( $_POST as $k=>$elem )
    echo"\nk : $k, elem: $elem<br>";
  echo"\nREQUESTS:<br>";
  foreach( $_REQUEST as $k=>$elem )
    echo"\nk : $k, elem: $elem<br>";
  if( 0/*isset($_FILES)*/ )
  {
    echo"\nFILES:<br>";
    foreach( $_FILES as $k=>$elem )
      echo"\nk : $k, elem: $elem<br>";
  }
}
global $_E;
$_E['mn'] = $_REQUEST["mn"];
$_E['bodyClass'] = "main";
$_E['bodyId'] = "main";
$exitus="you don't exist. Go away!";
include("mn.prj");
include("tee.inc");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN"
"http://www.w3.org/TR/html4/DTD/strict.dtd">
<html>
<head>
<title>Sahara
</title>
<meta http-equiv="content-type" content="text/html;charset=utf-8">
<link rel="stylesheet" href="./erica.css" media="screen" title="erica Stylesheet" />
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
