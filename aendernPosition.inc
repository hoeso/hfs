<?php
/** 1. aufrufendes Skript **** Variable *****************************************
 * editieren Angebot : ID(=EDV.ID)
 *                   : zumVaschiam
 *                   : woVaschiam
 *                   : doVaschiam
 *                   : 
 *****************************************************************************/
//$zumVaschiam="Position";
//$woVaschiam="EDVID";
//$doVaschiam="Angebot";
if( !isset($_REQUEST["zumVaschiam"])
    or !isset($_REQUEST["woVaschiam"])
    or !isset($_REQUEST["doVaschiam"])
    or !isset($_A["Richtung"])
  )
{ echo $exitus; return; }
$sql="SELECT $_REQUEST[zumVaschiam], $_REQUEST[woVaschiam] FROM $_REQUEST[doVaschiam] WHERE ID=" . $_E['ID'];
$arr[0]=0;   // Position
$arr[1]=1;   // Fremdschluessel

gibFelderArray( $MySQLDb, $sql, $arr );
$position=$arr[0];
if( !$position )
{
  echo"\ninterner Programmfehler mit '$sql'. Bitte verst&auml;ndigen Sie Ihren Systemadministrator<br>";
  include("knopfZurueck.inc");
  exit;
}
if( "kleiner" == $_A['Richtung'] )
{
  if( 1 == $position )
  {
    echo"\n<center>Der Eintrag befindet sich bereits an $_REQUEST[zumVaschiam] 1<br>";
    $wZu="anbietendKnopfZurueck";
    include("forkZu.inc");
  }
  $posMinus=$position-1;
  $sql="UPDATE $_REQUEST[doVaschiam] SET $_REQUEST[zumVaschiam]='parken' WHERE ID=" . $_E['ID'];
  $result = mysql_db_query( $MySQLDb, $sql );
  if(!$result)
     reagierenAufSQLFehler( $lkid, $sql, $id );
     // Jetzt ist diese Position frei und kann neu vergeben werden
  $sql="UPDATE $_REQUEST[doVaschiam] SET $_REQUEST[zumVaschiam]='$position' WHERE $_REQUEST[woVaschiam]=$arr[1] AND $_REQUEST[zumVaschiam]='$posMinus'";
  $result = mysql_db_query( $MySQLDb, $sql );
  if(!$result)
     reagierenAufSQLFehler( $lkid, $sql, $id );
     // Jetzt nur noch die urspruengliche Position dekrementieren
  $sql="UPDATE $_REQUEST[doVaschiam] SET $_REQUEST[zumVaschiam]='$posMinus' WHERE ID=" . $_E['ID'];
  $result = mysql_db_query( $MySQLDb, $sql );
  if(!$result)
     reagierenAufSQLFehler( $lkid, $sql, $id );
}
if( "groesser" == $_A['Richtung'] )
{
  $maxPos=gibFeld( $MySQLDb, "SELECT MAX($_REQUEST[zumVaschiam]) FROM $_REQUEST[doVaschiam] WHERE $_REQUEST[woVaschiam]=$arr[1]", 0 );
  if( $position >= $maxPos )
  {
    echo"\n<center>Der Eintrag befindet sich bereits an Position $position, also am Ende der Liste<br>";
    include("knopfZurueck.inc");
    exit;
  }
  $posPlus=$position+1;
  $sql="UPDATE $_REQUEST[doVaschiam] SET $_REQUEST[zumVaschiam]='parken' WHERE ID=" . $_E['ID'];
  $result = mysql_db_query( $MySQLDb, $sql );
  if(!$result)
     reagierenAufSQLFehler( $lkid, $sql, $id );
     // Jetzt ist diese Position frei und kann neu vergeben werden
  $sql="UPDATE $_REQUEST[doVaschiam] SET $_REQUEST[zumVaschiam]='$position' WHERE $_REQUEST[woVaschiam]=$arr[1] AND $_REQUEST[zumVaschiam]='$posPlus'";
  $result = mysql_db_query( $MySQLDb, $sql );
  if(!$result)
     reagierenAufSQLFehler( $lkid, $sql, $id );
     // Jetzt nur noch die urspruengliche Position inkrementieren
  $sql="UPDATE $_REQUEST[doVaschiam] SET $_REQUEST[zumVaschiam]='$posPlus' WHERE ID=" . $_E['ID'];
  $result = mysql_db_query( $MySQLDb, $sql );
  if(!$result)
     reagierenAufSQLFehler( $lkid, $sql, $id );
}
$goto=true;//dann wird gleich wieder zurueckgesprungen mittels javascript
?>
