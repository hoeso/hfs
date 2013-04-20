<?
// Input: 
// $_E['rootDocuments']

if( isset($_REQUEST["preparedocC"]) )
  hiddenFeldSchreiben( "docC", $_REQUEST["preparedocC"] );

$debug = 0;
if( $debug ) echo "AuftragID, $AuftragID<br>BerichtNr $berichtNr<br>";
$str = $AuftragID . "-" . $berichtNr . ".odt";
?>
<ol>
<li>
Dr&uuml;cken Sie auf <em>Durchsuchen ...</em> und
w&auml;hlen Sie in dem darauf folgenden Dialog ihre Datei aus:
</li>
<input type=file name=datei VALUE=$str size=80>
<li>
Senden Sie Ihre Datei mit <em>senden</em> an uns:
<input type=submit value='senden'>
</li>
</ol>
