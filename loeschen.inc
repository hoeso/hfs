<?
/************ Input ****************************************************************
 * $delTab                        : Tabelle, aus der ein Satz geloescht werden soll
 * $_E['ID']                      : Der Primaerschluessel des Datensatzes
 * $loeschenVorspiel              : bestimmte Entitaeten erzwingen eine Abzweigung
 *                                : vor dem eigentlichen Loeschen.
 *                                : Name der Entitaet + der aufzurufende Automat
 *                                : stehen in diesem Array
 * $fLoeschenVorspielWurdeBedient : Flag muss nach einer erzwungenen Abzweigung
 *                                : auf true stehen. Ansonsten wird die Abzweigung
 *                                : endlos oft aufgerufen.
 *                                : Am Ende des aufgerufenen Automaten muss wieder
 *                                : dieses Modul includiert sein
 *                                : 
 ***********************************************************************************/
/************************
 * das Loeschen verzweigt entsprechend des Array
 * eintrags aus loeschenVorspiel
 *
 * Das Loeschen muss vorher ueber das Setzen
 * $geprueft = true;
 * fuer die Tabelle freigegeben werden
 **********************************************/
/************************
 * Ueberwachung der referentiellen Integritaet
 * unter Angabe des Menuepunkts, an dem
 * zuerst geloescht werden muss
 **********************************************/

$bremse = false;

$c=count($arrRefs);
if( isset($arrRefs[$delTab]) )
{ // die generierten Abhaengigkeiten ( ~/public_html/db$ mysqldump -d -uregula erica | ./refIntegrity.pl > ../loeschBar.prj ) durchlaufen 
  foreach( $arrRefs[$delTab] as $refTab )
  {
    if( "1-leaf" == $refTab )
    { // ist eine Blatttabelle, also eine reine Entitaet ohne zu pruefenden foreign key
      $geprueft = true;
      break;
    }
    $sql="SELECT COUNT(*) FROM $refTab WHERE $refTab.$delTab" . "ID={$_E['ID']}";
    $treffer = gibFeld( $MySQLDb, $sql, 0 );
    if( $treffer )
    {// das sind die bestehenden Referenzen
      echo"\nEs existieren noch $treffer Verweise auf diesen Eintrag unter ";
      echo"\n<!-- Referenz in $refTab -->";
      $bremse = true;
      //if( (!isset($gPaketID) or "" == $gPaketID ) and "Paket" == $delTab )
        //$gPaketID=$_E['ID'];
      $sql=$Select["$refTab"];
      if( !$sql )
      {// kann nicht gefischt werden
        echo"<em>$Verweis[$refTab]</em>.<p>";
        continue;
      }
      if( strstr( $sql, "WHERE" ) )
        $sql .= " AND ";
      else
        $sql .= " WHERE ";
      $sql .= "$refTab.$delTab" . "ID={$_E['ID']}";
      $sql=str_replace( " ", "%20", $sql );
      if( isset($ID1) )
        $strID1="&ID1=$ID1";
      else
        $strID1='';
      if( "Gutschrift" == $refTab )
        $fKeinUpdate = $fKeinDelete = 'true';
      else
        $fKeinUpdate = $fKeinDelete = '';
      echo"\n<!-- $sql -->";
      echo"\n<A HREF=\"./mn.php?mn=1433&b=$sql&c=Eintr&auml;ge%20in%20$refTab%20mit%20Bezug%20zu%20$delTab&a=$refTab$strID1&fKeinUpdate=$fKeinUpdate&fKeinDelete=$fKeinDelete\">";
      if( isset($Verweis[$refTab]) )
        echo $Verweis[$refTab];
      else
        echo $refTab;
      ?></A>.<p><?
    }
    $geprueft = true;
  }
}

if( $bremse )
{
  echo"\nDeshalb darf dieser Eintrag noch nicht gel&ouml;scht werden<br>";
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
if( !$geprueft )
{
  echo"\n<p>Das L&ouml;schen dieser Eintr&auml;ge wird noch nicht verifiziert und deshalb wird es vorerst noch blockiert.<br>";
  echo"\n<!-- Tabelle $delTab -->";
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
echo"\n<h4>$delTab</h4>";

if( isset($Select[$delTab]) )
{
  $sql=$Select[$delTab];
  if( strstr( $sql, "WHERE" ) )
    $sql .= " AND ";
  else
    $sql .= " WHERE ";
  $sql .= $delTab . ".ID={$_E['ID']}";
}
else
  $sql="SELECT * FROM $delTab WHERE ID={$_E['ID']}";

anzeigen( $MySQLDb, $sql, "ohne submit Knopf", isset($ActionSuffix)?$ActionSuffix:"" );

if( !isset($_E['loeschen']) )
{
  echo"\n<h4>Soll dieser Eintrag gel&ouml;scht werden?</h4>";

  if( isset($backupSELECTSL1) )
    $strbackup="&backupSELECTSL1=$backupSELECTSL1";
  else
    $strbackup="";

  unset( $candies );
  if( isset($_eCandy) )
    foreach( $_eCandy as $k => $elem )
      if( $elem )
        $candies .= "&$k=$elem";
  if( !isset($candies) )
    $candies="";
  formularBeginnen( "./mn.php?mn=1142&a=$delTab&ID={$_E['ID']}$strbackup&force=true&ID1=$ID1$candies", "NAME='frm'");
  if( isset($_REQUEST["preparedocC"]) )
    hiddenFeldSchreiben( "docC", $_REQUEST["preparedocC"] );
  else if( isset($_REQUEST["prepforkdocC"]) )
    hiddenFeldSchreiben( "forkdocC", $_REQUEST["prepforkdocC"] );
  if( isset($_REQUEST["docZustand"]) )
    hiddenFeldSchreiben( "docZustand", $_REQUEST["docZustand"] );
  if( isset($_REQUEST["fKeinVorspann"]) )
    hiddenFeldSchreiben( "fKeinVorspann", $_REQUEST["fKeinVorspann"] );
  formularKnopf( "ja ...", "delete" );
  ?>&nbsp;&nbsp;&nbsp;<?
	formularKnopf( "nein ...", "dont" );
	formularBeenden();
?>
<script language=javascript type='text/javascript'>
<!--
	document.frm.dont.focus()
// -->
</script>
<?
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
else if( false == isset($fLoeschenVorspielWurdeBedient) and isset($loeschenVorspiel["$delTab"]) )
{
  $_E['wZu'] = $loeschenVorspiel[$delTab];
  include("forkZu.inc");
}

/*** es darf geloescht werden ... ***/
$sql="DELETE FROM $delTab WHERE ID={$_E['ID']}";
$result = mysql_db_query( $MySQLDb, $sql );
//echo"\n<!-- $sql -->";
if(!$result)
{
	reagierenAufSQLFehler( $lkid, $sql, $PKViolation );
}
else
{
	echo"\n<p>Der Eintrag wurde gel&ouml;scht.<br>";
}
?>
