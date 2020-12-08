<?php
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
      if( !isset($sqlAbbrev[$refTab]) )
      {
        ?><p>... Referenzierung nicht m&ouml;glich.<br>
        Eintrag f&uuml;r <em><?php echo $refTab;?></em> muss erg&auml;nzt werden in Modul entitySQLAbbrev.prj.<p><?php
        $_E['wZu']="anbietendKnopfZurueck";
        include("forkZu.inc");
      }
      $sql .= $sqlAbbrev[$refTab] . ".$delTab" . "ID={$_E['ID']}";
      $sql=urlencode( $sql ); // wg. SELECT mit CONCAT(...href=...)
      if( isset($ID1) )
        $strID1="&ID1=$ID1";
      else
        $strID1='';
      if( "Gutschrift" == $refTab )
        $fKeinUpdate = $fKeinDelete = 'true';
      else
        $fKeinUpdate = $fKeinDelete = '';
      echo"\n<!-- urldecode($sql) -->";
      $str = "\n<A HREF=\"./mn.php?mn=1433&b=$sql&c=Eintr&auml;ge%20in%20$refTab%20mit%20Bezug%20zu%20$delTab&a=$refTab$strID1&fKeinUpdate=$fKeinUpdate&fKeinDelete=$fKeinDelete";
      if( isset($_REQUEST["d"]) )
        $str .= "&d";
      echo $str;
      if( isset($_REQUEST['navi']) )
        echo "&navi=" . $_REQUEST['navi'];
      echo "\">";
      if( isset($Verweis[$refTab]) )
        echo $Verweis[$refTab];
      else
        echo $refTab;
      ?></A><?php
      include "loeschen.prj";
      ?>.<p><?php
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
if( !isset($geprueft) || !$geprueft )
{
  echo"\n";
  ?><p>Deleting those instances is not yet authorized and thus it is refused.<br>
  In your db-SubDir ~/public_html/db/ do:<br>
  <code>$ mysqldump -d sarscov2t | ./refIntegrity.pl > ../deleteConditions.prj</code><br>
  to allow deleting those instances<br>
  <?php
  echo"\n<!-- Tabelle $delTab -->";
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
echo"\n<h4>$delTab</h4>";

if( isset($Select[$delTab]) )
{
  if( !isset($sqlAbbrev[$delTab]) )
  {
    ?><p>... Referenzierung nicht m&ouml;glich.<br>
    Eintrag f&uuml;r <em><?php echo $delTab;?></em> muss erg&auml;nzt werden in Modul entitySQLAbbrev.prj.<p><?php
    $_E['wZu']="anbietendKnopfZurueck";
    include("forkZu.inc");
  }
  $sql=$Select[$delTab];
  if( strstr( $sql, "WHERE" ) )
    $sql .= " AND ";
  else
    $sql .= " WHERE ";
  $sql .= $sqlAbbrev[$delTab] . ".ID={$_E['ID']}";
}
else
  $sql="SELECT * FROM $delTab WHERE ID={$_E['ID']}";

anzeigen( $MySQLDb, $sql, "ohne submit Knopf", isset($ActionSuffix)?$ActionSuffix:"" );

if( !isset($_E['loeschen']) )
{
  echo"\n<h4>That instance shall be deleted?</h4>";

  if( isset($backupSELECTSL1) )
    $strbackup="&backupSELECTSL1=$backupSELECTSL1";
  else
    $strbackup="";

  unset( $candies );
  $candies="";
  if( isset($_eCandy) )
    foreach( $_eCandy as $k => $elem )
      if( $elem )
        $candies .= "&$k=$elem";
  formularBeginnen( "./mn.php?mn=1142&a=$delTab&ID={$_E['ID']}$strbackup&force=true&ID1=$ID1$candies", "NAME='frm'");
  if( isset($_REQUEST["preparedocC"]) )
    hiddenFeldSchreiben( "docC", $_REQUEST["preparedocC"] );
  else if( isset($_REQUEST["prepforkdocC"]) )
    hiddenFeldSchreiben( "forkdocC", $_REQUEST["prepforkdocC"] );
  if( isset($_REQUEST["docZustand"]) )
    hiddenFeldSchreiben( "docZustand", $_REQUEST["docZustand"] );
  if( isset($_REQUEST["fKeinVorspann"]) )
    hiddenFeldSchreiben( "fKeinVorspann", $_REQUEST["fKeinVorspann"] );
  formularKnopf( "yes ...", "delete" );
  ?>&nbsp;&nbsp;&nbsp;<?php
	formularKnopf( "no ...", "dont" );
	formularBeenden();
?>
<script language=javascript type='text/javascript'>
<!--
	document.frm.dont.focus()
// -->
</script>
<?php
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
	echo"\n<p>The instance has been removed.<br>";
  if( isset($_E) and isset($_E['entitaet']) and isset($_eCandy) and isset($_eCandy[$_E['entitaet']]) )
  {
    $sql = "SELECT MAX(ID) FROM " . $_E['entitaet'];
    $result = mysql_db_query( $MySQLDb, $sql );
    $arr = mysql_fetch_row( $result );
    $_eCandy[$_E['entitaet']] = $arr[0]; // damit wird auf die gerade angelegte Instanz in ihrer Liste positioniert
    mysql_free_result( $result );
  }
}
?>
