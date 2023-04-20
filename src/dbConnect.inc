<?php
/************ Input **********************************************************
 *****************************************************************************/
if( isset($_REQUEST["d"]) )
{
  $a_ = explode( "/", __file__ );
  $b_ = $a_[count($a_)-1];
}
if( isset($_REQUEST["d"]) )
  dEcho( $b_, "wZu: " . $_E['mn'] );

require_once ("connectMariaDB.inc");
include ("connect.prj");

if( isset($_REQUEST["d"]) )
  dEcho( $b_, "Trace : prepare DB-connect<br>read httpd.conf ..." );

// Verbinden zum MySQL-Server
$str = $_E['projekt'] . 'Host';
if( !isset($_SERVER[$str]) )
{
  ?>fatal error when connecting your project-DB ...
  <br>please set your projects db-configuration in /etc/apache2/conf-available/<?php echo $_E['projekt']?>.conf:<p>
  <ol>
  <li>
  <b>
  SetEnv <?php echo $_E['projekt']?>Host "localhost"<br>
  SetEnv <?php echo $_E['projekt']?>DB     "office"<br>
  SetEnv <?php echo $_E['projekt']?>DBuser "hfs"<br>
  SetEnv <?php echo $_E['projekt']?>DBpw   ""<p>
  </b>
  when done, enable your conf:
  </li>
  <li>
  <b>
  sudo a2enconf <?php echo $_E['projekt']?><p>
  </b>
  and reload your web-server<br>
  e.g. on debian:
  <li>
  <b>
  sudo systemctl reload apache2
  </b>
  </li>
  </ol>
  <?php
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
$host = $_SERVER[$str];
if( isset($_REQUEST["d"]) )
  dEcho( $b_, "httpd.conf::$str = $host" );
$str = $_E['projekt'] . 'DBuser';
$user = $_SERVER[$str];
if( isset($_REQUEST["d"]) )
  dEcho( $b_, "httpd.conf::$str = $user" );
$str = $_E['projekt'] . 'DBpw';
$pw = $_SERVER[$str];
$str = $_E['projekt'] . 'DB';
$MySQLDb = $_SERVER[$str];
if( isset($_REQUEST["d"]) )
  dEcho( $b_, "httpd.conf::$str = $MySQLDb" );

// Datenbank wählen
$succ=false;
if( isset($_REQUEST["d"]) )
  dEcho( $b_, "try to connect project-database ..." );
verbindenMitMySQLServer( $lkid, $host, $user, $pw );

verbindenMitMySQLDB( $succ, $MySQLDb, $lkid );
if( !$succ )
{
  echo "\nconnecting DB <b>$MySQLDb</b> was not successful<br>";
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
if( isset($_REQUEST["d"]) )
  dEcho( $b_, " ok." );

/************ Output *******************
 * $MySQLDb
 * $lkid
 *
 *
 ***************************************/
?>
