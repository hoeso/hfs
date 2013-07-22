<?php
class Datei
{
  protected $fp;
  private $pfad;

  function __construct($d, $mode="r")
  {
    $this->pfad = $d;
    $this->fp = fopen( $d, $mode );
    if( !$this->fp )
    {
      throw new Exception("Fehler beim &Ouml;ffnen von $d.", 1 );
      return;
    }
    //fclose( $this->fp );
  }
  function __get($var)
  {
    switch($var)
    {
      case 'handle':
        return $this->fp;
      case 'lesbar':
        return $this->fp <> 0;
      default:
        throw new Exception("Datei hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
}
