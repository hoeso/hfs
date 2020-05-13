<?php
$arrFK = array(
/*zum Kopieren:
	""=>array( // ich bin die Entitaet
		"",// ich bin ein Fremdschluessel
	),
*/
	"Ort"=>array( // ich bin die Entitaet
		"Trainer",// ich bin ein Fremdschluessel
	),
	"ProbandAdresse"=>array( // ich bin die Entitaet
		"Adresse",// ich bin ein Fremdschluessel
	),
	"ProbandMassnahme"=>array( // ich bin die Entitaet
		"Massnahme",// ich bin ein Fremdschluessel
	),
	"Termin"=>array(
		"Kategorie",
		"KW",
		"Tag",
		"Trainer",
		"VS",
	),
	"Vormerkung"=>array( // ich bin die Entitaet
		"Ort",// ich bin ein Fremdschluessel
	),
);
?>
