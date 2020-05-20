<?php
/************ Input **********************************************************
 * _E[leafDoc]      : Proband-Wurzelverzeichnis im Dokumenten-Pool
 *                  - dorthin wird gespeichert
 * _A[extension]    : Extension des Archivs (.odt)
 * _A[rawDoc] 	    : Vorlage
 * _A[xml]    	    : content.xml oder style.xml
 * _A['xmlStream']  : generiertes Dokument als Speicherobjekt
 * _A[archiveRawDoc]: Dokumenten-Vorlage vv.odt
 * _A[doc]    	    : Dateiname des zu erzeugenden Dokuments
 *            	    : 
 *****************************************************************************/
$debug=1;
/*** 1. generierten Inhalt in content.xml bzw. styles.xml zwischenspeichern ***/
$content = $_E['leafDoc'] . "/" . $_A['xml'];
if( $debug ) echo "dokument nach $content<br>";
if( "5" <= $versionPHP[0] )
{
 if( !file_put_contents( $content, $_A['xmlStream'] ) )
  {
    $modul=$_SERVER['PHP_SELF'];
    echo"\n$modul : interner Fehler 02 mit $content<br>";
    $_E['wZu']="anbietendKnopfZurueck";
    include("forkZu.inc");
  }
}

if( $debug ) echo "neues Archiv = $_A[doc]. alter Inhalt: $_A[xml]<br>";
if( $debug )
{
  if (($list = $_A['archiveRawDoc']->listContent()) == 0) {
    die("Error : ".$_A['archiveRawDoc']->errorInfo(true));
  }

  for ($i=0; $i<sizeof($list); $i++) {
    for(reset($list[$i]); $key = key($list[$i]); next($list[$i])) {
      echo "File $i / [$key] = ".$list[$i][$key]."<br>";
    }
    echo "<br>";
  }
}

/*** 2. alte Vorlage aus neuem Archiv loeschen                       ***/
if( !$_A['archiveRawDoc']->delete( PCLZIP_OPT_BY_NAME, $_A['xml'] ) )
{
  $modul=$_SERVER['PHP_SELF'];
  $str = $_A['archiveRawDoc']->errorInfo(true);
  echo"\n$modul : interner Fehler 05 beim L&ouml;schen von $_A[xml]:" . $str . "<br>";
  if( PCLZIP_ERR_NO_ERROR == $str )
    echo"\nM&ouml;glicherweise ist in htdocs kein Schreibrecht gesetzt<br>";
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}

/*** 6. neuen Inhalt ins Archiv schreiben                            ***/
if( !$_A['archiveRawDoc']->add( $content, PCLZIP_OPT_REMOVE_ALL_PATH ) )
{
  $modul=$_SERVER['PHP_SELF'];
  echo"\n$modul : interner Fehler 06 beim Schreiben von $content<br>";
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
?>
