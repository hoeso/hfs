<?php
/************ Input **********************************************************
 *****************************************************************************/
if( isset($_REQUEST['d']) )
{
  $a_ = explode( "/", __file__ );
  $b_ = $a_[count($a_)-1];
}
include ("connect.prj");
include ("verbindenMitMySQL.inc");
if( isset($_REQUEST["d"]) )
  dEcho( $b_, "httpd.conf lesen ..." );
// Verbinden zum MySQL-Server
$str = $_E['projekt'] . 'Host';
$host = $_SERVER[$str];
if( isset($_E['enableDbg']) && $_E['enableDbg'] )
  echo"<br>httpd.conf::$str = $host";
$str = $_E['projekt'] . 'DBuser';
$user = $_SERVER[$str];
if( isset($_E['enableDbg']) && $_E['enableDbg'] )
  echo"<br>httpd.conf::$str = $user";
$str = $_E['projekt'] . 'DBpw';
$pw = $_SERVER[$str];
$str = $_E['projekt'] . 'DB';
$MySQLDb = $_SERVER[$str];
if( isset($_E['enableDbg']) && $_E['enableDbg'] )
  echo"<br>httpd.conf::$str = $MySQLDb";

if( isset($_E['enableDbg']) && $_E['enableDbg'] )
  echo "\n<br>jetzt verbinden ...<br>";

if( isset($_REQUEST["d"]) )
  dEcho( $b_, "connect request --> mysql-db" );
verbindenMitMySQLServer( $lkid, $host, $user, $pw );
if( isset($_REQUEST["d"]) )
  dEcho( $b_, "connect request beendet." );
if( !$lkid )
{
  echo"\nkeine Verbindung zu MySQL m&ouml;glich($user).<br>";
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
if( isset($_E['enableDbg']) && $_E['enableDbg'] )
  echo "\n von MySQL@$host Link $lkid erhalten ...<br>";
// Datenbank wählen
$succ=false;
if( isset($_E['enableDbg']) && $_E['enableDbg'] )
  echo "\nverbinden zur DB $MySQLDb ...";
verbindenMitMySQLDB( $succ, $MySQLDb, $lkid );
if( !$succ )
{
  echo "\nEs ist ein Fehler aufgetreten beim Versuch, mit der Datenbank $MySQLDb Verbindung aufzunehmen<br>";
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
if( isset($_E['enableDbg']) && $_E['enableDbg'] )
  echo "  ok.";
/************ Output *******************
 * $MySQLDb
 * $lkid
 *
 *
 ***************************************/
include "Db.php";
$Db = Db::getInstance();
$Db->link = $lkid;
$Db->db = $MySQLDb;
?>
