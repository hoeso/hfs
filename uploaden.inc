<?php
//
//  Diese Datei wird aufgerufen, NACHDEM das Hochladen der Datei(en)
//  abgeschlossen ist. $_FILES enthaelt nun die an den Upload uebergebenen Datei(en)
//
//  Fehlermeldungen:
//  0:  Die Datei wurde fehlerfrei hochgeladen
//  1:  Die hochgeladene Datei ueberschreitet die in der Anweisung
//      upload_max_filesize in php.ini festgelegte Groesse
//  2:  Die hochgeladene Datei ueberschreitet die in dem HTML Formular mittels der Anweisung
//      MAX_FILE_SIZE angegebene maximale Groesse
//  3:  Die Datei wurde nur teilweise hochgeladen
//  4:  Es wurde keine Datei hochgeladen.
//  Referenz: http://www.php.net/manual/de/features.file-upload.errors.php
//
//  Im vorliegenden Hochladebericht koennen alle Fehler ignoriert werden, wenn der Dateiname
//  die leere Zeichenreihe ist.
//

$fehlergrund=array(
  "Die Datei wurde fehlerfrei hochgeladen",
  "Die hochzuladende Datei ueberschreitet die maximale in php.ini erlaubte Groesse",
  "Die hochzuladende Datei überschreitet die im Formular festgelegte Größe",
  "Die Datei wurde nur teilweise hochgeladen",
  "Es wurde keine Datei hochgeladen",
);
$debug = 0;
if( false == isset( $_FILES ) )
{
  echo"du muassd scho was ogehm!"; exit;
}

foreach( $_FILES as $k=>$elem )
{
  $feldname = $k;
  if ($_FILES[$k]["name"] != "" )
  {
    foreach( $_FILES[$k] as $l=>$elem2 )
    {
      if($debug) echo "\nelem: $l -- $elem2<br>";
      switch ( $l )
      {
        case "error":
          if( 0 <> $elem2 )
          {
            echo "wegen dem technischem Fehler Nr $elem2 konnte die Datei nicht hochgeladen werden.<br>";
	    echo "Fehlerursache: $fehlergrund[$elem2]<br>";
            $_E['wZu']="anbietendKnopfZurueck";
            include("forkZu.inc");
          }
        break;
        case "name":
          $name=$elem2;
        break;
        case "tmp_name":
          $tmp_name=$elem2;
        break;
      }
    }
  
    /*** Datei                                              speichern ***/
    $_A['dateiPfad'] = $_E['rootDocuments'] . "/" . $name;
    if( false == move_uploaded_file($tmp_name, $_A['dateiPfad']) )
    {
      ?>Die Datei <?php echo $_A['dateiPfad'];?> konnte nicht gespeichert werden<br><?php
    }
    else
    {
      echo $_A['dateiPfad'];?> wurde gespeichert<br><?php
      $_E['wZu']="verarbeitendUpload";
      include("forkZu.inc");
    }
  }
}
?>
