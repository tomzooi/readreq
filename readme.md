Readme
====
To make a requirements editor/display to make concise networked requirements that store to JSON

#Features
- simple tab based editor for requirements (vim like?) with live viewport
- automatic numbering and stuff
  - parser for viewing in latex 
  - (possibly html?)
  - latex automatic referencing?
	
#requirements format
filename: Requirements_for.Prefix.req


    level						description		(label)
    "will, should, might etc"	"description"	"label"<br>
        "children of this requirement..."<br>
         "..."
#example
filename: The_system.F.req


        should	  be able to export requirements to latex easily	      latexport
	        will	use a commandline based program for this			latexcmd

#JSON
filename: The_system.f.req.json


	{
		"requirements"	: [
			{"level": "should", "description":"be able to export requirements to latex easily", "label":"latexport", "children":[
				{"level":"should", "description":"use a commandline based program for this", "label":"latexcmd"}
				]
			}
		]
	}

#formatting
F1: The system should be able to export requirements to latex easily
	F1.1: The system will use a commandline based program for this

#Latex
