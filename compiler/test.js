

function upvote_all()
{
    let topic = 20851;
    let p = 1;

    function upvote(cmt) {
        let topic = 20851;
        $.ajax({
            type: 'POST',
            url: 'https://forum.intra.42.fr/topics/' + topic + '/messages/' + cmt + '/votes/vote.json?kind=upvote',
            data: {upvote_count: 1, downvote_count: 0, totalvote_count: 1, kindvote_count: 1},
            async: false,
            success: function (response) {
                console.log(response);
            }
        });
    }
    console.log("Wait...");
    while (true) {
        let resp = $.ajax({
            type: 'GET',
            url: 'https://forum.intra.42.fr/topics/' + topic + '/messages/pagination/timed?page=' + p,
            data: {},
            async: false,
            success: function (response)  {
            }
        }).responseText;
        if (resp == null) {
            break;
        }
        let divs = resp.match(/div class='dancer from-down message-item' data-id='([0-9]*?)'[\s\S]*?div data-uid="upvote" data-state="(true|false)"/ig);
        if (divs == null) {
            break;
        }
        for (let i = 0; i < divs.length; ++i) {
            divs[i] = divs[i].replace(/div class='dancer from-down message-item' data-id='/, "");
            divs[i] = divs[i].replace(/'/g, "");
            divs[i] = divs[i].replace(/"/g, "");
            divs[i] = divs[i].replace(/data-index[\s\S]*?upvote data-state=/, "");
            let spl = divs[i].split(' ');
            if (spl[1] === 'true') {
                divs[i] = 0;
            }
            else {
                divs[i] = parseInt(spl[0]);
            }
        }
        for (let id of divs) {
            if (id !== 0) {
                upvote(id);
            }
        }
        console.log('Page ' + p + ' sent requests.');
        ++p;
    }
    console.log('All requests sent');
}

upvote_all();
////////////////////////////////////////////////////////////////////////////////


function post() {
    let n = 25;
    let topic = 20863;

    function randomInteger(min, max) {
        let rand = min + Math.random() * (max + 1 - min);
        rand = Math.floor(rand);
        return rand;
    }
    function makeid() {
        let languages = ["BASIC","ASharp.NET","A-0System","A+","A++","ABAP","ABC","ABCALGOL","ABSET","ABSYS","ACC","Accent","ACL2","LGP-30","Action!","ActionScript","Actor","Ada","Adenine","Agdatheoremprover","AgilentVEE","Agora","AIMMS","Aldor","Alef","AlgebraicLogicFunctional","ALGOL58","ALGOL60","ALGOL68","ALGOLW","Alice","Alma-0","AmbientTalk","AmigaE","AMOS","AMPL","AngelScript","Apex","APL","AppInventorforAndroid","AppleScript","APT","Arc","ARexx","Argus","AspectJ","Assemblylanguage","ATS","AtejiPX","AutoHotkey","Autocoder","AutoIt","AutoLISP","Averest","AWK","Axum","ActiveServerPages","B","Babbage","Ballerina","BashUnixshell","BASIC","Bc","BCPL","BeanShell","Batchfile","Bertrand","BETA","BLISS","Blockly","BlooPandFlooP","Boo","Boomerang","Bourneshell","BashUnixshell","Kornshell","BusinessBasic","C","C--","C++","C*","CSharp","C/AL","CachéObjectScript","CShell","Caml","Cayenne","CDuce","Cecil","Cesil","Céu","Ceylon","CFEngine","Cg","Chcomputerprogramming","Chapel","Charity","Charmlanguage","CHILL","CHIP-8","Chomski","ChucK","Cilk","Citrine","AS/400ControlLanguage","Claire","Clarion","Clean","Clipper","CLIPS","CLIST","Clojure","CLU","CMS-2","COBOL","CobolScript","Cobra","CoffeeScript","ColdFusion","COMAL","Combined","COMIT","CommonIntermediateLanguage","CommonLisp","COMPASS","ComponentPascal","ConstraintHandlingRules","COMTRAN","Cool","Coq","Coral66","CorVision","COWSEL","CPL","Cryptol","Crystal","Csound","Communicatingsequentialprocesses","Cuneiform","Curl","Curry","Cybil","Cyclone","Cython","D","Datapoint'sAdvancedSystemsLanguage","Dart","Darwin","DataFlex","Datalog","DATATRIEVE","DBase","Dccomputerprogram","DIGITALCommandLanguage","DinkSmallwood","DIBOL","Dog","Draco","Dragon","DRAKON","Dylan","DYNAMO","Dataanalysisexpressions","E","Ease","PL/I","Easytrieve","EC","ECMAScript","EdinburghIMP","EGL","Eiffel","ELAN","Elixir","Elm","EmacsLisp","Emerald","Epigram","Easy","Eltron","Erlang","EsUnixshell","Escher","ExecutiveSystemsProblemOrientedLanguage","Esterel","Etoys","Euclid","Euler","Euphoria","EusLispRobot","CMSEXEC","EXEC2","ExecutableUML","Ezhil","F","FSharp","F*","Factor","Fantom","FAUST","FFP","Fjölnir","FL","Flavors","Flexlanguage","BlooPandFlooP","FLOW-MATIC","FOCAL","FOCUS","FOIL","FORMAC","Formulalanguage","Forth","Fortran","Fortress","FP","FranzLisp","F-Script","GameMakerLanguage","GameMonkeyScript","GeneralAlgebraicModelingSystem","GAPcomputeralgebrasystem","G-code","GDScript","Genie","GeometricDescriptionLanguage","GEORGE","GLSL","GNUE","Go","Go!","GameOrientedAssemblyLisp","Gödel","Golo","MAD","GoogleAppsScript","Gosu","IBM1620","GPSS","ComputerSciencesCorporation","GRASS","Grasshopper3D","Groovy","Hack","HAGGIS","HAL/S","Halide","HamiltonCshell","Harboursoftware","Hartmannpipeline","Haskell","Haxe","Hermes","HighLevelAssembly","HighLevelShaderLanguage","TempleOS","Hopsoftware","Hopscotch","Hope","Hugo","Humelanguage","HyperTalk","Io","Icon","IBMBasicassemblylanguage","IBMBASICA","IBMHAScript","IBMInformix-4GL","IBMRPG","Irineu","IDL","Idris","Inform","J","JSharp","VisualJ++","JADE","JALcompiler","Janusconcurrentconstraint","Janustime-reversiblecomputing","JASS","Java","JavaFXScript","JavaScript","JobControlLanguage","JEAN","JoinJava","JOSS","Joule","JOVIAL","Joy","JScript","JScript.NET","Julia","Jython","K","Kaleidoscope","Karel","IntelliCorpSoftware","KiXtart","Klerer-MaySystem","KnowledgeInterchangeFormat","Kojo","Kotlin","KentRecursiveCalculator","KRL","KUKARobotLanguage","KRYPTON","Kornshell","KoduGameLab","Kivyframework","LabVIEW","Ladderlogic","LANSAdevelopmentenvironment","Lasso","Lava","LC-3","Legoscript","LittleImplementationLanguage","LilyPond","Limbo","Limnor","LINC4GL","Lingo","LINQ","LIS","LanguageforInstructionSetArchitecture","Lisp","Lite-C","Lithe","Littleb","Ethereum","Logo","Logtalk","LotusScript","LPC","LSE","LindenScriptingLanguage","LiveCode","LiveScript","Lua","Lucid","Lustre","LYaPAS","Lynx","MUMPS","M2001","M4computerlanguage","MSharp","Machinecode","MAD","MAD","Magik","Magmacomputeralgebrasystem","Maudesystem","Máni","Maplesoftware","MAPPER","MARKIVsoftware","Mary","MicrosoftMacroAssembler","MATH-MATIC","Mathematica","MATLAB","Maximasoftware","Macsyma","Maxsoftware","Autodesk3dsMax","MayaEmbeddedLanguage","MDL","Mercury","Mesa","Metafont","MHEG-5","Microassembler","MicroScript","MIIS","Milk","MIMIC","Mirah","Miranda","MIVAScript","ML","Model204","Modelica","Modula","Modula-2","Modula-3","Mohols","MOO","Mortran","Mouse","MPD","Mathcad","CommonIntermediateLanguage","MIRCscriptinglanguage","MUMPS","MuPAD","Ethereum","MysticBBS","NetwideAssembler","Napier88","Neko","Nemerle","NESL","Net.Data","NetLogo","NetRexx","NewLISP","NEWP","Newspeak","NewtonScript","Nial","Nice","Nickle","Nickle","Nim","NORD","NoteXactlyC","NotQuiteC","NullsoftScriptableInstallSystem","Nu","NWScript","NXT-G","O:XML","Oak","Oberon","OBJ2","ObjectLisp","ObjectLOGO","ObjectREXX","ObjectPascal","Objective-C","Objective-J","Obliq","OCaml","Occam","Occam-π","GNUOctave","OmniMark","Onyx","Opa","Opal","OpenCL","OpenEdgeAdvancedBusinessLanguage","Open","OpenVera","OPS5","OptimJ","Orc","ORCA/Modula-2","Orielscriptinglanguage","Orwell","Oxygene","Oz","P","P4","P′′","ParaSail","PARI/GP","Pascal","PascalScript","PCASTL","forComputableFunctions","PEARL","PeopleCode","Perl","PerlDataLanguage","Perl6","Pharo","PHP","Pico","Picolisp","Pict","Pigprogrammingtool","Pike","PIKTpagedoesnotexist","PILOT","Hartmannpipeline","Pizza","PL-11","PL/0","forBusiness","PL/C","PL/I","PL/M","PL/P","PL/SQL","PL360","PLANC","Plankalkül","Planner","PLEX","PLEXIL","Plus","POP-11","POP-2","PostScript","AmigaE","POV-Ray","Powerhouse","PowerBuilder","PowerShell","Polymorphic","Processing","Processing.js","Prograph","PROIV","Prolog","PROMAL","Promela","PROSEmodelinglanguage","Protel","ProvideX","Pro*C","Pure","PureBasic","PureData","Python","QfromKxSystems","QSharp","Qalb","QtScript","QuakeC","Quantumprogramming","R","R++","Racket","RAPID","Rapira","Ratfiv","Ratfor","Rc","Reason","REBOL","Red","CoreWar","REFAL","REXX","Ring","Rlab","ROOP","IBMRPG","RPL","RobotBattle","RTL/2","Ruby","RuneScript","Rust","S","S2","S3","S-Lang","S-PLUS","SA-C","SabreTalk","SAIL","SAM76","SASSystem","SASL","Sather","Sawzall","Scala","Scheme","Scilab","Scratch","Script.NET","Sed","Seed7","Self","SenseTalk","SequenceL","Ethereum","SETL","Superbasedatabase","SIGNAL","SiMPLE","SIMSCRIPT","Simula","Simulink","Singularityoperatingsystem","SISAL","SLIP","SMALL","Smalltalk","StandardML","Strongtalk","Snap!","SNOBOL","SPITBOLcompiler","Snowball","SecureOperationsLanguage","Solidity","SOPHAEROS","SPARK","Speakeasycomputationalenvironment","Speedcoding","ParallaxPropeller","SP/k","IBM1401SymbolicProgrammingSystem","SQL","SQR","Squeak","Squirrel","SR","S/SL","Starlogo","Strand","Stata","Stateflow","Subtext","Superbasedatabase","SuperCollider","SuperTalk","Swift","Swiftparallelscriptinglanguage","SYMPL","SystemVerilog","T","TACL","TACPOL","TADS","TransactionApplicationLanguage","Tcl","Tea","TextEditorandCorrector","TELCOMP","TeX","TextExecutive","TensilicaInstructionExtension","TMGlanguage","Tompatternmatchinglanguage","TOMobject-oriented","Toi","Clarion","TextProcessingUtility","TRAC","TTM","Transact-SQL","Transcript","TTCN","Turing","TUTOR","TXL","TypeScript","Tynker","Ubercode","UCSDPascal","Umple","Unicon","Uniface","UNITY","Unixshell","UnrealScript","Vala","Verilog","VHDL","Vimtexteditor","Ethereum","VisualBasic","VisualBasic.NET","VisualDataFlex","VisualDialogScript","VisualFortran","VisualFoxPro","VisualJ++","VisualJ","AutoLISP","VisualObjects","VisualProlog","VSXu","WATFIV","WebAssembly","WebDNA","Whiley","Winbatch","WolframLanguage","Wyvern","X++","X10","XBase","XBase++","XBL","XC","XCoreXS1","XHarbour","XL","Xojo","XOTcl","XOD","XPath","XPL","XPL0","XQuery","XSB","XSharp","XSLTransformations","Xtend","Yorick","YQL","Yoix","Znotation","Zebra","Zeno","ZetaLisp","ZOPL","Zshell","ZPL","Z++","APL","Assemblylanguage","BASIC","C","C++","CSharp","COBOL","Elixir","Fortran","Go","ApacheGroovy","Haskell","Java","JavaScript","Julia","Kotlin","Lisp","Lua","MATLAB","Objective-C","OCaml","Pascal","Perl","PHP","Python","R","Ruby","Rust","Scala","Shellscript","Smalltalk","Swift","TypeScript","VisualBasic.NET",];
        let result = randomInteger(0, languages.length);
        return result;
    }
    for (let i = n; i; i--) {
        $.ajax({
            type: 'POST',
            url: 'https://forum.intra.42.fr/topics/'+ topic + '/messages',
            data: {'utf8': '✓', 'message[content]': makeid()},
            success: function (response) {
                console.log(response);}})
    }
}
post();

////////////////////////////////////////////////////////////////////////////////