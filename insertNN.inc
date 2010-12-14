<?
/**********************************************
 * Übergabe einer einmaligen Zuordnung
 * es wird geprüft, ob diese bereits existiert
 * falls noch nicht, wird die Zuordnung angelegt
 ***********************************************/

$HTTP_POST_VARS = $_POST;
if( !isset( $HTTP_POST_VARS ) )
{
  ?>Die &Uuml;bergabedaten k&ouml;nnen nicht gelesen werden<br>
  Verst&auml;ndigen Sie ihren Systemadministrator<br>
  <ul>M&ouml;gliche Fehlerursachen
  <li>Die Formulardaten wurden nicht mit METHOD='POST' gesendet
  <ul><?
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
reset( $HTTP_POST_VARS );

// erst mal pruefen, ob die Verknuepfung vielleicht schon existiert
// weil sie muss einmalig sein

foreach( $HTTP_POST_VARS as $k=>$elem )
{
  switch( $k )
  {
    case "TabelleM":
      $arr[ 'Tabelle' ] = $elem;	// 1. Element ist die Verknuepfungstabelle
    break;
    case "TabelleA":
      $arr[ 'Feld1' ] = $elem . "ID";
    break;
    case "SELECTA":
      $arr[ 'Wert1' ] = $elem;
    break;
    case "TabelleB":
      $arr[ 'Feld2' ] = $elem . "ID";
    break;
    case "SELECTB":
      $arr[ 'Wert2' ] = $elem;
    break;
  }
}
$succ = gibEinmaligenRecord( $MySQLDb, $arr, $sql, $nTreffer );
if( !$succ )
{
  ?>Es ist ein Fehler aufgetreten beim Ueberpr&uuml;fen, ob die Zuordnung in der Tabelle <?
  echo $TabelleM;
  ?> schon vorhanden ist<?
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
$sqlGibRecord=$sql;

$str2 = strstr( $sql, " WHERE" );
if( isset($debug) && $debug )
    echo "\n$str2<br>";
$strSelect = str_replace( $str2, "", $sql );// $str1 ist ohne WHERE-Klausel
if( isset($debug) && $debug )
    echo "\n$strSelect<br>";

$sqlAlle = $Select[$TabelleM];
if( isset($OrderBy[$TabelleM]) )
    $sqlAlle .= $OrderBy[$TabelleM];
if( $nTreffer > 0 )
{
unset($tabKopf);
unset($id);
unset($zeilen);
auslesenZuordnung( $MySQLDb, $sql, $tabKopf, $id, $zeilen );
$zeilen[0]=str_replace(">","",$zeilen[0]);
if( isset($debug) && $debug )
    echo "\n$sql<br>";
switch( $TabelleB )
{
  case "Hintergrundfarbe":
     $var="$" . $zeilen[0] . "_" . $tabKopf[1];
     $f=false;

     unset($ar);
     $ar=file($resourceDatei);// aus connect.inc
     for($i=0;$i<count($ar);$i++)
     {
	$aTmp = explode( "=", $ar[$i] );
	if( ( $aTmp[0] == $var ) )
	{
	    $aTmp[1]=$zeilen[1];
	    $ar[$i]="$aTmp[0]='$aTmp[1]';\n";
	    $f=true;
	    break;
	}
     }	     
     if( $f )	// Variable wurde gefunden
     {
	    $fp=fopen($resourceDatei, "w+");
	    for($i=0;$i<count($ar);$i++)
	    {
		fputs($fp, $ar[$i]);
		}
	    fclose($fp);
     }
  break;
  default:
    ?>Die gew&auml;hlte Zuordnung existiert bereits<br><?
  break;
}
  anzeigenTabelle( $tabKopf, $zeilen, "center" );
  include("linkFortsetzen.inc");
  echo "\n<hr><center>Vorhandene Eintr&auml;ge";
  anzeigen( $MySQLDb, $sqlAlle, $TabelleM, "" );
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}

$sql = "INSERT INTO $TabelleM (ID";
// Die Variablen kommen in der Reihenfolge Tabellenname, Primaerschluessel-Feld

foreach( $HTTP_POST_VARS as $k=>$elem )
{
	switch( $k )
	{
		case "TabelleA":
		case "TabelleB":
		     $sql .= ", $elem"."ID";
		     break;
	}
}
$sql .= " ) VALUES ( null";
reset( $HTTP_POST_VARS );
foreach( $HTTP_POST_VARS as $k=>$elem )
{
	switch( $k )
	{
		case "SELECTA":
		case "SELECTB":
		     $sql .= ", $elem";
		     break;
	}
}
$sql .= " )";
$result = mysql_db_query( $MySQLDb, $sql );
$fAendern=false;
if(!$result)
{
	switch( $TabelleB )
	{
	case "Hintergrundfarbe":
	     $sql2="select * from $TabelleB where ID=$SELECTB";
	     $farbe = gibFeld( $MySQLDb, $sql2, 2 );
	     $sql2="select * from $TabelleA where ID=$SELECTA";
	     $fenster = gibFeld( $MySQLDb, $sql2, 1 );
	     $var="$" . $fenster . "_" . $TabelleB;
	     $f=false;

	     unset($ar);
	     $ar=file($resourceDatei);// aus connect.inc
	     for($i=0;$i<count($ar);$i++)
	     {
		$aTmp = explode( "=", $ar[$i] );
		if( ( $aTmp[0] == $var ) )
		{
		    $aTmp[1]=$farbe;
		    $ar[$i]="$aTmp[0]='$aTmp[1]';\n";
		    $f=true;
		    break;
		}
	     }	     
	     if( $f )	// Variable wurde gefunden
	     {
		    $fp=fopen($resourceDatei, "w+");
		    for($i=0;$i<count($ar);$i++)
		    {
			fputs($fp, $ar[$i]);
			}
		    fclose($fp);
	     }
	     $fAendern=true;
	break;
	default:
		reagierenAufSQLFehler( $lkid, $sql, $PKViolation );
		if( $PKViolation )
		    $fAendern=true;
		else
			include("linkFortsetzen.inc");
	break;
	}
}
else
{
	echo "\nDer Eintrag wurde gespeichert";
	echo "\n<hr>";
	echo "\n<center>Vorhandene Eintr&auml;ge";
	anzeigen( $MySQLDb, $sqlAlle, $TabelleM, "" );
}
if( !$fAendern )
{
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}

if( $fUpdateB )
{
	$A_ID=$arr[ 'Feld1' ];
	$A_FKWert=$arr[ 'Wert1' ];
}
$sql = "SELECT ID FROM $TabelleM WHERE $A_ID=$A_FKWert";
$ID = gibFeld( $MySQLDb, $sql, 0 );
if( !$ID )
{
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
if( $fUpdateB )
{
	$B_ID=$arr[ 'Feld2' ];
	$B_FKWert=$arr[ 'Wert2' ];
}
$sql = "UPDATE $TabelleM SET $B_ID=$B_FKWert WHERE ID=$ID";
$result = mysql_db_query( $MySQLDb, $sql );
if(!$result)
{
  reagierenAufSQLFehler( $lkid, $sql, $PKViolation );
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
?>
