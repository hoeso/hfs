<?php
if( isset($_REQUEST["d"]) )
{
  $a_ = explode( "/", __file__ );
  $b_ = $a_[count($a_)-1];
}
$arrNichtAendern=array (
/* zum Kopieren
"",
*/
"Zeitstempel"
);
if( isset($debug) && $debug )
  echo "anzeigen der Tabelle '{$_E['entitaet']}' ...<br>";
if( !isset( $suffix ) )
  $suffix="";
lesenRETabelle( $result, $MySQLDb, $_E['entitaet'], $suffix );
if( !$result && isset($debug) && $debug )
{
  echo "Ist die Tabelle '{$_E['entitaet']}' leer?<br>";
  return;
}
$str=$_E['entitaet'];
$str=str_replace( "ae", "&auml;", $str );
spaltenNamenHolen( $result, $spaltenName );
if( isset($debug) && $debug )
{
  $n = count($spaltenName);
  echo"\nSpaltenzahl = $n<br>";
}

// --- Anzeige formatieren
$auchIDausgeben = false;
// ist Zieltabelle Teil der URL?
$iFarbReihe=0;
foreach( $_eCandy as $k => $elem )
  if( $k == $_E['entitaet'] and isset($_REQUEST["$k"]) )
  {
    $iFarbReihe=$elem;
    break;
  }
tabelleBeginnen();
if( !isset($cSpalten) )
  $cSpalten="";
ausgebenAlsTabellenkopf( $spaltenName, $auchIDausgeben, $cSpalten, "", "", "" );

if( false==isset($keinInsert) )
{
  // Zeile fuer neuen Eintrag...
  tabellenZeileBeginnen();
  $actio = "./mn.php?mn=";
  if( isset($_E) && isset($_E['reInsertWo']) )
    $actio .= $_E['reInsertWo'];
  else
    $actio .= "9422";
  $actio .= "&a={$_E['entitaet']}&b={$_E['entitaet']}%20wird%20gespeichert%20...";
  if( isset($_E["navi"]) )
    $actio .= "&navi=" . $_E["navi"];
  if( isset($_REQUEST["d"]) )
    $actio .= "&d";

  formularBeginnen( $actio, "name=frm" . $_E['entitaet'] . " onSubmit='return pruefenEingaben(this)'" );
  hiddenFeldSchreiben( "Tabelle", $_E['entitaet'] );
  if( isset($_E) && isset($_E['FK2join']) && isset($_E['verbEntitaet']) && isset($_E['value2Join']) ) // nur wenn vollstaendig uebergeben
  {
    hiddenFeldSchreiben( "FK2join", $_E['FK2join'] );
    hiddenFeldSchreiben( "verbEntitaet", $_E['verbEntitaet'] );
    hiddenFeldSchreiben( "value2Join", $_E['value2Join'] );
    //hiddenFeldSchreiben( "d", $_E['FK2join'] );
  }
  if( !isset($enumListe[$_E['entitaet']]) )
    ausgebenAlsNeueTabellenzeile( $result, $_E['entitaet'] );
  else
    ausgebenAlsNeueTabellenzeile( $result, $_E['entitaet'], $enumListe[$_E['entitaet']] );
  ?><td><?php
  formularKnopf("neu anlegen", "");
  ?></td></form><?php
  tabellenZeileBeenden();
}
// listenRE.inc beendet die Tabelle
?>
