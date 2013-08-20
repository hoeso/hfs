<?php
// Input: 
// $_E['rootDocuments']

if( isset($_REQUEST["preparedocC"]) )
  hiddenFeldSchreiben( "docC", $_REQUEST["preparedocC"] );

$debug = 0;
if( $debug ) echo "AuftragID, $AuftragID<br>BerichtNr $berichtNr<br>";
//Pfad (und Namen) einstellen, mit dem der Upload gespeichert werden soll:
//$str = $AuftragID . "-" . $berichtNr . ".odt";
$str = $_E['rootDocuments'];
?>
<!-- ol> In Kommentar gesetzt, weil die Texte und der Submit-Button seit apache2 2.4.6-2 nicht mehr angezeigt werden
<li -->
1. Dr&uuml;cken Sie auf <em>Durchsuchen ...</em> und w&auml;hlen Sie in dem darauf folgenden Dialog ihre Datei aus:
<br>
<!-- /li -->
<input type=file name=datei value=<?php echo $str;?>? size=80>
<br><input type=file name=datei2 value=<?php echo $str;?>? size=80>
<!-- li-->
<br>
2. Senden Sie Ihre Datei ab:
<br>
<input type=submit value='senden'>
<!-- /li>
</ol -->
