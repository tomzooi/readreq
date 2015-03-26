Readme
====
To make a requirements editor/display to make concise networked requirements that store to JSON

#Features
- simple tab based editor for requirements (vim like?) with live viewport
- automatic numbering and stuff
  - parser for viewing in latex 
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


	\begin{easylist}
	\ListProperties(Style*=\textbf NF\textbf, Progressive*=3ex,Start1=1,FinalMark={})
	# \label{req:pocnormbehav} The POC should not impede any freedom of the users or invade his or hers normal behaviour too much
	# \label{req:pocusable} The POC will be usable by wheelchair users with as less assistance as possible
	# \label{req:pocsafe} The POC will be safe for users and the environment
	## \label{req:pocprivacy} The POC will keep users privacy
	## \label{req:pocnot harm} The POC will not harm the user
	# \label{req:pocscalable} The POC will not be scalable to all wheelchair users in Singapore
	# \label{req:pocsimple} The POC will be simple
	## \label{req:pochw} The POC will use existing hardware
	\end{easylist}

#Use

    readreq <inputfile> <outputfile>

will read the inputfile, put the JSON in the outputfile and display the latex in your console
