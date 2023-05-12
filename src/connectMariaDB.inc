<?php
include ("dbErrorHandler.inc");

$versionPHP = explode( ".", phpversion() ); 
if( "5" < $versionPHP[0] )
  include ("mysql_.inc");

// Verbinden zum MySQL-Server
function verbindenMitMySQLServer( &$lkid, $host, $user, $pw )
{
  $lkid = mysql_connect( $host, $user, $pw );
  return;
}

// Datenbank wählen
function verbindenMitMySQLDB( &$succ, $db, $lkid )
{
  $succ = mysql_select_db( $db, $lkid);
  if( !$succ )
  {
    reagierenAufSQLFehler( $lkid, "Oeffnen von $db", $dummy );
    return $succ;
  }

  if( isset( $debug ) && $debug )
    echo "Datenbank ist offen (smile)<br>";

  return $succ;
}
?>
