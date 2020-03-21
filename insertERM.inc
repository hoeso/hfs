<?php
/**********************************************
 * Übergabe von Primaerschluesseln aus reinen Entitaeten
 * und JE Tabellen und eigenen Attributen zum
 * Einfuegen.
 * Uebergabe-Parameter:
 * zielTabelle		Name der Tabelle, in die eingefuegt werden soll
 * TabelleSL[1-4]	Namen von bis zu 4 Tabellen, deren Primaerschluessel
 *                      in das Feld {TabelleSL[1-4]}ID eingetragen werden soll
 * TabelleRE[1-5]	Namen von bis zu 5 Tabellen, deren Primaerschluessel
 *                      in das Feld {TabelleRE[1-5]}ID eingetragen werden soll
 * TabelleMM[1-3]	Namen von bis zu 3 JE-Tabellen, deren Primaerschluessel
 *                      in das Feld {TabelleMM[1-3]}ID eingetragen
 *			 werden soll
 * SELECTRE[1-5]	 Die bis zu 5 Primaerschluessel der RE Tabellen
 * SELECTMM[1-3]	 Die bis zu 3 Primaerschluessel der JE
 *			  Tabellen
 * {zielTabelle}.{Feldtyp}.{Feldname}	Eine Liste von Attributen der
 *					Zieltabelle mit Angabe des
 *					 Feldtyps und -namens
 * es wird anhand der uebergebenen Primaerschluessel
 * geprüft, ob der Eintrag bereits existiert
 * falls noch nicht, wird der Datensatz angelegt
 ***********************************************/
$debug = 0;
if( isset($SELECTSL1) and $SELECTSL1 && !isset($backupSELECTSL1) )
    $backupSELECTSL1=$SELECTSL1;
$debugPK=false;

$HTTP_POST_VARS = $_POST;
if( !isset( $HTTP_POST_VARS ) )
{
  echo "Die Uebergabedaten k&ouml;nnen nicht gelesen werden<br>";
  echo "Verst&auml;ndigen Sie ihren Systemadministrator<br>";
  echo "<ul>M&ouml;gliche Fehlerursachen";
  echo "<li>Die Formulardaten wurden nicht mit METHOD='POST' gesendet";
  echo "<ul>";
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
reset( $HTTP_POST_VARS );

// erst mal pruefen, ob die Verknuepfung vielleicht schon existiert
// weil sie muss einmalig sein

unset( $arrPK );
foreach( $HTTP_POST_VARS as $k=>$elem )
{
  switch( $k )
  {
    case "TabelleRE1": // praeparierte RE FK-Tabellen
    case "TabelleRE2": // heissen wie die RE-Tabelle,
    case "TabelleRE3": // haben jedoch am Ende
    case "TabelleRE4": // zusaetzlich ein $-Zeichen
    case "TabelleRE5":
      if( '$' == $elem[ strlen($elem)-1 ] )
        $elem = substr( $elem, 0, -1 );
    case "TabelleRE1":
      $keyRE1 = $elem . "ID";
    case "TabelleRE2":
      $keyRE2 = $elem . "ID";
    case "TabelleRE3":
      $keyRE3 = $elem . "ID";
    case "TabelleRE4":
      $keyRE4 = $elem . "ID";
    case "TabelleRE5":
      $keyRE5 = $elem . "ID";
    break;
    case "TabelleID":
      $keyID = $elem . "ID";
    break;
    case "ID":
      $arrPK[ $keyID ] = $elem;
    break;
    case "TabellePK":
      $keyPK = $elem . "ID";
    break;
    case "PK":
      $arrPK[ $keyPK ] = $elem;
    break;
    case "TabelleSL1":
      $keySL1 = $elem . "ID";
      if( isset($_E['entitaet']) and !isset($_E['ID']) and $_E['entitaet'] = $k )
        $fOverlaySL1 = true;
    break;
    case "SELECTSL1":
      $arrPK[ $keySL1 ] = $elem;
      if( isset($fOverlaySL1) )
        $_E['ID'] = $elem;
    break;
    case "TabelleSL2":
      $keySL2 = $elem . "ID";
    break;
    case "SELECTSL2":
      $arrPK[ $keySL2 ] = $elem;
    break;
    case "TabelleSL3":
      $keySL3 = $elem . "ID";
    break;
    case "SELECTSL3":
      $arrPK[ $keySL3 ] = $elem;
    break;
    case "TabelleSL4":
      $keySL4 = $elem . "ID";
    break;
    case "SELECTSL4":
      $arrPK[ $keySL4 ] = $elem;
    break;
    case "TabelleRE1":
      $keyRE1 = $elem . "ID";
    break;
    case "SELECTRE1":
      $arrPK[ $keyRE1 ] = $elem;
    break;
    case "TabelleRE2":
      $keyRE2 = $elem . "ID";
    break;
    case "SELECTRE2":
      $arrPK[ $keyRE2 ] = $elem;
    break;
    case "TabelleRE3":
      $keyRE3 = $elem . "ID";
    break;
    case "SELECTRE3":
      $arrPK[ $keyRE3 ] = $elem;
    break;
    case "TabelleRE4":
      $keyRE4 = $elem . "ID";
    break;
    case "SELECTRE4":
      $arrPK[ $keyRE4 ] = $elem;
    break;
    case "TabelleRE5":
      $keyRE5 = $elem . "ID";
    break;
    case "SELECTRE5":
      $arrPK[ $keyRE5 ] = $elem;
    break;
    case "TabelleEM1":
      $keyEM1 = $elem . "ID";
    break;
    case "SELECTEM1":
      $arrPK[ $keyEM1 ] = $elem;
    break;
    case "TabelleEM2":
      $keyEM2 = $elem . "ID";
    break;
    case "SELECTEM2":
      $arrPK[ $keyEM2 ] = $elem;
    break;
    case "TabelleEM3":
      $keyEM3 = $elem . "ID";
    break;
    case "SELECTEM3":
      $arrPK[ $keyEM3 ] = $elem;
    break;
    case "TabelleMM1":
      $keyMM1 = $elem . "ID";
    break;
    case "SELECTMM1":
      $arrPK[ $keyMM1 ] = $elem;
    break;
    case "TabelleMM2":
      $keyMM2 = $elem . "ID";
    break;
    case "SELECTMM2":
      $arrPK[ $keyMM2 ] = $elem;
    break;
    case "TabelleMM3":
      $keyMM3 = $elem . "ID";
    break;
    case "SELECTMM3":
      $arrPK[ $keyMM3 ] = $elem;
    break;
    case "d":
      // Debug-Flag ignorieren
    break;
    case "UniquePK":
      // Das Flag ignorieren
    break;
    case "ID1":
      // Die ID der 1. RE-Tabelle (= Filter) ignorieren
    break;
    case "zielTabelle":
      $table = $elem;
    break;
    case "zielT":	// Manchmal heisst sie auch so
      $zielTabelle=$elem;
      $table = $elem;
    break;
    default:
      $str = substr( $k, 0, 6 );
      if( !strcmp( "hidden", $str ) )
        break;
      $arrAttr[ $k ] = $elem;
    break;
  }
  // case zielTabelle.switch typ 
}
if( $debug )
{
  if( count($arrPK ) )
    foreach( $arrPK as $k=>$elem )
    {
      echo "\nPK: $k -- $elem<br>";
    }
  if( count($arrAttr ) )
    foreach( $arrAttr as $k=>$elem )
    {
      echo "\nAttr: $k -- $elem<br>";
    }
}
if( $debugPK )
{
  echo "\n$PKTabelle<br>";
  echo "\n$PK<br>";
}

$nTreffer = 0;

if( isset($UniquePK) and $UniquePK )
{
  $succ = suchenMitPK( $MySQLDb, $table, $arrPK, $nTreffer, $globalID, $arr );
  if( !$succ )
  {
    echo "\nEs ist ein Fehler aufgetreten beim Ueberpr&uuml;fen,";
    echo "ob der Datensatz in der Tabelle $table schon vorhanden ist<br>";
    $_E['wZu']="anbietendKnopfZurueck";
    include("forkZu.inc");
  }
  if( $nTreffer > 0 )
  {
    if( $debug )
      echo "\n$sql<br>";
    echo "\nDieser Eintrag existiert bereits: ";
    for( $i=0; $i<count($arr); $i++ )
      echo "\n $arr[$i]";
    echo "\n<br>";
    $autoID=$globalID;
  }
}
if( $debug )
  if( count($arrAttr) )
    foreach( $arrAttr as $k=>$elem )
    {
      echo "\nAttr: $k -- $elem<br>";
    }
if( $debug )
  echo "\n$sql<br>";
if( !$nTreffer )
{
  if( !isset($UniquePK) )
    $UniquePK="";
  $gespeichert = speichernPKsUndAttr( $lkid, $MySQLDb, $table,$arrPK, $arrAttr, $UniquePK, $sql, $autoID );
  if( !$gespeichert )
  {
    $AusgabeUnterdruecken=true;
    reagierenAufSQLFehler( $lkid, $sql, $PKViolation );
    if( $PKViolation )
    {
      ?>UNIQUE KEY VIOLATION<p><?php
    }
    if( 0 == $autoID )
    {
      $_E['wZu']="anbietendKnopfZurueck";
      include("forkZu.inc");
    }
    else
    {
      ?>autoID ist versorgt.<br><?php
    }
    if( $table == $globalTab )
      $globalID=$autoID;
  }
}
if( $gespeichert )
{
  echo "\nDer Eintrag wurde gespeichert<br>";

  if( isset($zielTabelle) )
  {
    $sql = "SELECT LAST_INSERT_ID() FROM " . $zielTabelle;
    $result = mysql_db_query( $MySQLDb, $sql );
    $arr = mysql_fetch_row( $result );
    if( isset($globalTab) and $table == $globalTab )//nicht, wenn Aufruf aus Administration
    {
      $globalID=$arr[0];
    }
    $autoID=$arr[0];
    mysql_free_result( $result );
  }
}
?>
