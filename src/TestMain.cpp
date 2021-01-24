/**
* @file   TestMain.cpp
* @author Michael R. Hayashi
* @date   18 October 2018
* @brief  Primary Function for Input/Solver/Output Control Modes
*/

#define _USE_MATH_DEFINES // Place before including <cmath> for e, log2(e), log10(e), ln(2), ln(10), pi, pi/2, pi/4, 1/pi, 2/pi, 2/sqrt(pi), sqrt(2), and 1/sqrt(2)
#include <parser-spef/parser-spef.hpp>
#include "limboint.hpp"
#include "solnoutclass.hpp"
#include "layeredFdtd.hpp"

// Manipulate namespace
using std::cerr;
using std::cout;
using std::endl;

/// @brief main function 
/// @param argc number of arguments 
/// @param argv values of arguments 
/// @return 0 if succeed 
int main(int argc, char** argv)
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "--help") == 0)
        {
            cout << "Help for LayoutAnalyzer binary (with main testing features)" << endl;
            cout << "Usage: mpirun LayoutAnalyzer options file1 [file2..file3]" << endl;
            cout << "Options:" << endl;
            cout << "  --help                Display this information." << endl;
            cout << "  --version             Print the version number." << endl;
            cout << "  -r, --read            Read given GDSII file into memory and display statistics." << endl;
            cout << "  -p, --parrot          Immediately output given GDSII file after reading." << endl;
            cout << "  -w, --write           Write database in memory to given SPEF file." << endl;
            cout << "  -i, --imp             Read given interconnect modeling platform file and write GDSII file with name also given." << endl;
            cout << "  -t, --pslg            Read GDSII files of design and outline and write a PSLG file for each layer." << endl;
            cout << "  -s, --simulate        Read GDSII and sim input files, simulate, and write solution to Xyce (SPICE) subcircuit." << endl;
            cout << "  -sx, --xyce           Identical to \"-s\"." << endl;
            cout << "  -sp, --spef           Read GDSII and sim input files into memory, simulate, and write solution to SPEF file." << endl;
            cout << "  -sc, --citi           Read GDSII and sim input files into memory, simulate, and write solution to CITIfile." << endl;
            cout << "  -st, --touchstone     Read GDSII and sim input files into memory, simulate, and write solution to Touchstone file." << endl;
            cout << endl << "Comments:" << endl;
            cout << " The file passed after -r, --read, -p, or --parrot must be a Calma GDSII stream file." << endl;
            cout << " The file passed after -w or --write must be a blank SPEF file." << endl;
            cout << " The first file passed after -i or --imp must be a 3D description .imp file, and the second must be a blank .gds file." << endl;
            cout << " The first file passed after -t or --pslg must be a Calma GDSII stream file of the design, and the second must be a GDSII file of just the design's outline." << endl;
            cout << " The first file passed after -s or --simulate (or -sx or --xyce) must be a Calma GDSII stream file, the second must be a sim_input file, and the third must be a blank Xyce file." << endl;
            cout << " The first file passed after -sp or --spef must be a Calma GDSII stream file, the second must be a sim_input file, and the third must be a blank SPEF file." << endl;
            cout << " The first file passed after -sc or --citi must be a Calma GDSII stream file, the second must be a sim_input file, and the third must be a blank CITIfile." << endl;
            cout << " The first file passed after -sc or --citi must be a Calma GDSII stream file, the second must be a sim_input file, and the third must be a blank Touchstone file." << endl;
            cout << endl << "Bug reporting:" << endl;
            cout << "Visit <https://github.com/purdue-onchip/gds2Para>" << endl;
        }
        else if (strcmp(argv[1], "--version") == 0)
        {
            cout << "Version Number for LayoutAnalyzer binary (beta with main testing features): " << "0.2" << endl;
        }
        else
        {
            cerr << "Only \"--help\" or \"--version\" flags allowed without files passed" << endl;
        }
    }
    else if (argc == 3)
    {
        if ((strcmp(argv[1], "-r") == 0) || (strcmp(argv[1], "--read") == 0))
        {
            AsciiDataBase adb;
            string fName = argv[2];
            adb.setFileName(fName);
            GdsParser::GdsReader adbReader(adb);
            bool adbIsGood = adbReader(fName.c_str());
            vector<size_t> indCellPrint = { adb.getNumCell() - 1 };
            adb.print(indCellPrint);
        }
        else if ((strcmp(argv[1], "-p") == 0) || (strcmp(argv[1], "--parrot") == 0))
        {
            // Read and print existing GDSII file
            AsciiDataBase adb;
            string fName = argv[2];
            size_t indExtension = fName.find_last_of(".");
            adb.setFileName(fName.substr(0, indExtension) + "_parrot" + fName.substr(indExtension, string::npos));
            GdsParser::GdsReader adbReader(adb);
            bool adbIsGood = adbReader(fName.c_str());
            adb.print({ });

            // Dump to parroted file immediately
            adb.dump();
            cout << "Dumped parroted file" << endl;
        }
        else if ((strcmp(argv[1], "-w") == 0) || (strcmp(argv[1], "--write") == 0))
        {
            // Load sample information in memory
            string design = "test_out";
            Waveforms blank;

            // Setup the port information vector
            vector<Port> ports = {};
            ports.emplace_back(Port("inp1", 'I', 50., 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("u1:a", 'I', 50., 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("inp2", 'I', 50., 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("u1:b", 'I', 50., 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("out", 'O', 50.0, 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("u3:o", 'O', 50., 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("u1:o", 'O', 50., 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("u4:a", 'I', 50., 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("u4:o", 'O', 50., 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("f1:d", 'I', 50., 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("f1:a", 'O', 50., 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("u2:a", 'I', 50., 1, vector<double>(6, 0), -1));
            ports.emplace_back(Port("u4:b", 'I', 50., 1, vector<double>(6, 0), -1));

            // Setup the Eigen sparse conductance matrix
            spMat matG(13, 13); // Initialize sparse conductance matrix (S)
            vector<dTriplet> listG; // Initialize triplet list for conductance matrix
            listG.reserve(3); // Reserve room for 3 nonzero entries in each row
            listG.push_back(dTriplet(0, 0, 1. / (10.5e3)));
            listG.push_back(dTriplet(0, 1, -1. / (10.5e3)));
            listG.push_back(dTriplet(1, 0, -1. / (10.5e3)));
            listG.push_back(dTriplet(1, 1, 1. / (10.5e3)));
            listG.push_back(dTriplet(2, 2, 1. / (4.5e3)));
            listG.push_back(dTriplet(2, 3, -1. / (4.5e3)));
            listG.push_back(dTriplet(3, 2, -1. / (4.5e3)));
            listG.push_back(dTriplet(3, 3, 1. / (4.5e3)));
            listG.push_back(dTriplet(4, 4, 1. / (1.4e3)));
            listG.push_back(dTriplet(4, 5, -1. / (1.4e3)));
            listG.push_back(dTriplet(5, 4, -1. / (1.4e3)));
            listG.push_back(dTriplet(5, 5, 1. / (1.4e3)));
            listG.push_back(dTriplet(6, 6, 1. / (2.1e3)));
            listG.push_back(dTriplet(6, 7, -1. / (2.1e3)));
            listG.push_back(dTriplet(7, 6, -1. / (2.1e3)));
            listG.push_back(dTriplet(7, 7, 1. / (2.1e3)));
            listG.push_back(dTriplet(8, 8, 1. / (2.1e3)));
            listG.push_back(dTriplet(8, 9, -1. / (2.1e3)));
            listG.push_back(dTriplet(9, 8, -1. / (2.1e3)));
            listG.push_back(dTriplet(9, 9, 1. / (2.1e3)));
            listG.push_back(dTriplet(10, 10, 1. / (1.2e3 + 2.3e3 + 3.4e3) + 1. / (1.2e3 + 7.8e3 + 5.6e3)));
            listG.push_back(dTriplet(10, 11, -1. / (1.2e3 + 2.3e3 + 3.4e3)));
            listG.push_back(dTriplet(10, 12, -1. / (1.2e3 + 7.8e3 + 5.6e3)));
            listG.push_back(dTriplet(11, 10, -1. / (3.4e3 + 2.3e3 + 1.2e3)));
            listG.push_back(dTriplet(11, 11, 1. / (3.4e3 + 2.3e3 + 1.2e3) + 1. / (3.4e3 + 2.3e3 + 7.8e3 + 5.6e3)));
            listG.push_back(dTriplet(11, 12, -1. / (3.4e3 + 2.3e3 + 7.8e3 + 5.6e3)));
            listG.push_back(dTriplet(12, 10, -1. / (5.6e3 + 7.8e3 + 1.2e3)));
            listG.push_back(dTriplet(12, 11, -1. / (5.6e3 + 7.8e3 + 2.3e3 + 3.4e3)));
            listG.push_back(dTriplet(12, 12, 1. / (5.6e3 + 7.8e3 + 1.2e3) + 1. / (5.6e3 + 7.8e3 + 2.3e3 + 3.4e3)));
            matG.setFromTriplets(listG.begin(), listG.end()); // Assign nonzero entries to sparse conductance matrix
            matG.makeCompressed(); // Conductance matrix in compressed sparse row (CSR) format

            // Setup the Eigen sparse capacitance matrix
            spMat matC(13, 13); // Initialize sparse capacitance matrix (F)
            vector<dTriplet> listC; // Initialize triplet list for capacitance matrix
            listC.reserve(1); // Reserve room for 1 nonzero entry in each row
            listC.push_back(dTriplet(0, 0, 2.5e-15));
            listC.push_back(dTriplet(1, 1, 2.9e-15));
            listC.push_back(dTriplet(2, 2, 0.7e-15));
            listC.push_back(dTriplet(3, 3, 1.3e-15));
            listC.push_back(dTriplet(4, 4, 0.5e-15));
            listC.push_back(dTriplet(5, 5, 0.2e-15));
            listC.push_back(dTriplet(6, 6, 0.35e-15));
            listC.push_back(dTriplet(7, 7, 0.65e-15));
            listC.push_back(dTriplet(8, 8, 0.7e-15));
            listC.push_back(dTriplet(9, 9, 0.5e-15));
            listC.push_back(dTriplet(10, 10, 8.9e-15));
            listC.push_back(dTriplet(11, 11, 6.7e-15));
            listC.push_back(dTriplet(12, 12, 7.8e-15));
            matC.setFromTriplets(listC.begin(), listC.end()); // Assign nonzero entries to sparse capacitance matrix
            matC.makeCompressed(); // Capacitance matrix in compressed sparse row (CSR) format

            // Create variables of custom classes
            Parasitics sample(ports, matG, matC, { 1000. });
            SolverDataBase sdb(design, blank, sample);

            // Prepare to write to file
            string fName = argv[2];
            sdb.setOutSPEF(fName);
            sdb.print({});
            bool couldDump = sdb.dumpSPEF();
        }
        else
        {
            cerr << "Must pass a file after \"-r\", \"-p\", or \"-w\" flags, rerun with \"--help\" flag for details" << endl;
        }
    }
    else if (argc == 4)
    {
        if ((strcmp(argv[1], "-i") == 0) || (strcmp(argv[1], "--imp") == 0))
        {
            // Read interconnect modeling platform (IMP) file and write to GDSII file
            SolverDataBase sdb;
            string inIMPFile = argv[2];
            string outGDSIIFile = argv[3];
            bool sdbIsGood = sdb.readIMPwriteGDSII(inIMPFile, outGDSIIFile);
            cout << "File ready at " << outGDSIIFile << endl;
        }
        else if ((strcmp(argv[1], "-t") == 0) || (strcmp(argv[1], "--pslg") == 0))
        {
            // Read and print existing GDSII file
            AsciiDataBase adbDesign;
            string designFileName = argv[2];
            adbDesign.setFileName(designFileName);
            GdsParser::GdsReader adbReader(adbDesign);
            bool adbDesignGood = adbReader(designFileName.c_str());
            adbDesign.print({});

            // Read GDSII file of outline for PSLG purposes
            AsciiDataBase adbOutline;
            string outlineFileName = argv[2];
            adbOutline.setFileName(outlineFileName);
            GdsParser::GdsReader adbOutlineReader(adbOutline);
            bool adbOutlineGood = adbOutlineReader(outlineFileName.c_str());
            vector<complex<double>> outlinePt = adbOutline.findPoints(adbOutline.getCell(0).getCellName(), { 0., 0. }, strans());
            //vector<complex<double>> outlinePt = { complex<double>(+150e-6, -48.0e-6), complex<double>(+150e-6, +121e-6), complex<double>(-1.00e-6, +121e-6), complex<double>(-1.00e-6, -48.0e-6) }; // nand2 outline
            //vector<complex<double>> outlinePt = { complex<double>(+12.77e-6, -0.230e-6), complex<double>(+12.77e-6, +3.03e-6), complex<double>(-0.230e-6, +3.03e-6), complex<double>(-0.230e-6, -0.230e-6) }; // SDFFRS_X2 outline
            //vector<complex<double>> outlinePt = { complex<double>(+2.82e-3, +5.00e-5), complex<double>(+2.825e-3, +3.87e-3), complex<double>(+3.00e-5, +3.87e-3), complex<double>(+3.00e-5, +5.00e-5) }; // 4004 outline

            // Convert to planar straight-line graph (PSLG) file for external meshing
            vector<int> layers = adbDesign.findLayers();
            for (size_t indLayer = 0; indLayer < layers.size(); indLayer++)
            {
                adbDesign.convertPSLG(adbDesign.getCell(adbDesign.getNumCell() - 1).getCellName(), layers[indLayer], outlinePt);
            }
            cout << "Created PSLG file for each layer" << endl;
        }
        else
        {
            cerr << "Must pass a .imp file to read and blank GDSII file to write after \"-i\" flag, rerun with \"--help\" flag for details" << endl;
            cerr << "Must pass two related GDSII files to read after \"-t\" flag, rerun with \"--help\" flag for details" << endl;
        }
    }
    else if (argc == 5)
    {
        if ((strcmp(argv[1], "-s") == 0) || (strcmp(argv[1], "--simulate") == 0) || (strcmp(argv[1], "-sx") == 0) || (strcmp(argv[1], "--xyce") == 0) || (strcmp(argv[1], "-sp") == 0) || (strcmp(argv[1], "--spef") == 0) || (strcmp(argv[1], "-sc") == 0) || (strcmp(argv[1], "--citi") == 0) || (strcmp(argv[1], "-st") == 0) || (strcmp(argv[1], "--touchstone") == 0))
        {
            // Initialize SolverDataBase, mesh, and set variables for performance tracking
            clock_t t1 = clock();
            tf::Executor executor; // Executor of taskflow (optional constructor argument is number of threads, default is thread::hardware_concurrency())
            tf::Taskflow taskflow; // Taskflow graph
            AsciiDataBase adb;
            SolverDataBase sdb;
            fdtdMesh sys;
            int status = 0; // Initialize as able to return successfully
            bool adbIsGood, sdbIsGood, sdbCouldDump;

            // Get file names
            string inGDSIIFile = argv[2];
            string inSimFile = argv[3];
            size_t indExtension = inGDSIIFile.find_last_of(".");

            // Read GDSII file
            taskflow.name("TestMain");
            tf::Task taskA = taskflow.placeholder();
            taskA.name("Cmd Line / Initialize Vars");
            tf::Task taskB = taskflow.emplace([&]()
            {
                adb.setFileName(inGDSIIFile);
                GdsParser::GdsReader adbReader(adb);
                adbIsGood = adbReader(inGDSIIFile.c_str());
                if (adbIsGood)
                {
                    vector<size_t> indCellPrint = {}; // { adb.getNumCell() - 1 };
                    adb.print(indCellPrint);
                    cout << "GDSII file read" << endl;
                }
                else
                {
                    cerr << "Unable to read in GDSII file" << endl;
                    status = 1;
                    exit(status);
                }
            });
            taskB.name("Read GDSII");
            taskA.precede(taskB);

            // Read simulation input file
            tf::Task taskC = taskflow.emplace([&]()
            {
                sdbIsGood = sdb.readSimInput(inSimFile);
                if (sdbIsGood)
                {
                    cout << "Simulation input file read" << endl;
                }
                else
                {
                    cerr << "Unable to read in simulation input file" << endl;
                    status = 1;
                    exit(status);
                }
            });
            taskC.name("Read Sim Input");
            taskA.precede(taskC);

            // Append information so far to fdtdMesh
            unordered_set<double> portCoorx, portCoory;
            tf::Task taskD = taskflow.emplace([&]()
            {
                string topCellName = adb.getCell(adb.getNumCell() - 1).getCellName();
                adb.saveToMesh(topCellName, { 0., 0. }, strans(), &sys, sdb.findLayerIgnore()); // Recursively save GDSII conductor information to sys
            });
            taskD.name("GDSII Info to Solver");
            taskB.precede(taskD);
            tf::Task taskE = taskflow.emplace([&]()
            {
                sdb.convertToFDTDMesh(&sys, adb.getNumCdtIn(), &portCoorx, &portCoory); // Save simulation input information to sys
            });
            taskE.name("Sim Input to Solver");
            taskC.precede(taskE);
            taskD.precede(taskE);

            // Mesh the domain and mark conductors
            unordered_map<double, int> xi, yi, zi;
            clock_t t2 = clock();
            tf::Task taskF = taskflow.emplace([&](auto &subflow)
            {
                status = meshAndMark(&sys, &xi, &yi, &zi, subflow);
                if (status == 0)
                {
                    cout << "meshAndMark dynamic tasking Success!" << endl;
                    cout << "meshAndMark dynamic tasking time is " << (clock() - t2) * 1.0 / CLOCKS_PER_SEC << " s" << endl << endl;
                }
                else
                {
                    cerr << "meshAndMark dynamic tasking Fail!" << endl;
                    exit(status);
                }
                //sys.print();
            });
            taskF.name("Mesh and Mark");
            taskE.precede(taskF);

            // Set D_eps and D_sig
            clock_t t3 = clock();
            tf::Task taskG = taskflow.emplace([&]()
            {
                status = matrixConstruction(&sys);
                if (status == 0)
                {
                    cout << "matrixConstruction Success!" << endl;
                    cout << "matrixConstruction time is " << (clock() - t3) * 1.0 / CLOCKS_PER_SEC << " s" << endl << endl;
                }
                else {
                    cerr << "matrixConstruction Fail!" << endl;
                    exit(status);
                }
                //sys.print();
            });
            taskG.name("D_{eps} / D_{sig}");
            taskF.precede(taskG);

            // Set port
            clock_t t4 = clock();
            tf::Task taskH = taskflow.emplace([&](auto &subflow)
            {
                status = portSet(&sys, xi, yi, zi, subflow);
                if (status == 0)
                {
                    cout << "portSet dynamic tasking Success!" << endl;
                    cout << "portSet dynamic tasking time is " << (clock() - t4) * 1.0 / CLOCKS_PER_SEC << " s" << endl << endl;
                }
                else
                {
                    cerr << "portSet dynamic tasking Fail!" << endl;
                    exit(status);
                }
                //sys.print();
            });
            taskH.name("Port Set");
            taskF.precede(taskH);

            // Generate Stiffness Matrix
#ifndef SKIP_GENERATE_STIFF
            clock_t t5 = clock();
            tf::Task taskI = taskflow.emplace([&]()
            {
                status = generateStiff(&sys);
                if (status == 0)
                {
                    cout << "generateStiff Success!" << endl;
                    cout << "generateStiff time is " << (clock() - t5) * 1.0 / CLOCKS_PER_SEC << " s" << endl << endl;
                }
                else
                {
                    cerr << "generateStiff Fail!" << endl;
                    exit(status);
                }
            });
            taskI.name("Generate S");
            taskG.precede(taskI);
#endif

            // Write object sys to files
#ifndef SKIP_WRITE_SYS_TO_FILE
            WriteSysToFile(sys);
#endif

            // Parameter generation
            clock_t t6 = clock();
            tf::Task taskJ = taskflow.emplace([&](auto &subflow)
            {
                // Calculate Z-parameters
                status = paraGenerator(&sys, subflow);

                // Fake Z-parameters
                /*sys.x.assign(sys.numPorts * sys.numPorts * sys.nfreq, complex<double>(-1., 0.)); // Fake data of resistive network to get overhead when timing
                for (size_t indi = 0; indi < sys.nfreq; indi++)
                {
                    for (size_t indj = 0; indj < sys.numPorts; indj++)
                    {
                        for (size_t indk = 0; indk < sys.numPorts; indk++)
                        {
                            if (indi == indj)
                            {
                                sys.x[indi * (sys.numPorts * sys.numPorts) + indj * sys.numPorts + indk] = sys.numPorts; // Correct diagonal entry
                            }
                        }
                    }
                }*/

                if (status == 0)
                {
                    cout << "paraGenerator dynamic tasking Success!" << endl;
                    cout << "paraGenerator dynamic tasking time is " << (clock() - t6) * 1.0 / CLOCKS_PER_SEC << " s" << endl << endl;
                }
                else
                {
                    cerr << "paraGenerator dynamic tasking Fail!" << endl;
                    exit(status);
                }
                //sys.print();
                cout << "Engine time to this point: " << (clock() - t2) * 1.0 / CLOCKS_PER_SEC << " s" << endl;
                cout << "Total time to this point: " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << " s" << endl << endl;
            });
            taskJ.name("Generate Z-param");
            taskG.precede(taskJ);
            taskH.precede(taskJ);

            // Network parameter storage
            tf::Task taskK = taskflow.emplace([&]()
            {
                Parasitics newPara = sdb.getParasitics(); // Start with outdated parastics to update
                newPara.saveNetworkParam('Z', sdb.getSimSettings().getFreqsHertz(), sys.x); // Save the Z-parameters in fdtdMesh to Parasitics class
                sdb.setParasitics(newPara);
            });
            taskK.name("Z-param to Storage");
            taskJ.precede(taskK);

            // Select Output File Based on Control Mode
            tf::Task taskL = taskflow.emplace([&]()
            {
                cout << endl;
                if ((strcmp(argv[1], "-sp") == 0) || (strcmp(argv[1], "--spef") == 0))
                {
                    // Output SPEF file
                    string outSPEFFile = argv[4];
                    vector<size_t> indLayerPrint = { 0, 1 * sdb.getNumLayer() / 3, 2 * sdb.getNumLayer() / 3, sdb.getNumLayer() - 1 }; // {}; // Can use integer division
                    sdb.setDesignName(adb.findNames().back());
                    sdb.setOutSPEF(outSPEFFile);
                    sdb.print(indLayerPrint);
                    bool sdbCouldDump = sdb.dumpSPEF();
                    cout << "File ready at " << outSPEFFile << endl << endl;
                }
                else if ((strcmp(argv[1], "-sc") == 0) || (strcmp(argv[1], "--citi") == 0))
                {
                    // Convert to S-parameters
                    Parasitics newPara = sdb.getParasitics(); // Start with copy of parastics to reinterpret
                    newPara.convertParam('S');
                    sdb.setParasitics(newPara);

                    // Output Common Instrumentation Transfer and Interchange file (CITIfile)
                    string outCITIFile = argv[4];
                    vector<size_t> indLayerPrint = { 0, 1 * sdb.getNumLayer() / 3, 2 * sdb.getNumLayer() / 3, sdb.getNumLayer() - 1 }; // {}; // Can use integer division
                    sdb.setDesignName(adb.findNames().back());
                    sdb.setOutCITI(outCITIFile);
                    sdb.print(indLayerPrint);
                    bool sdbCouldDump = sdb.dumpCITI();
                    cout << "File ready at " << outCITIFile << endl << endl;
                }
                else if ((strcmp(argv[1], "-st") == 0) || (strcmp(argv[1], "--touchstone") == 0))
                {
                    // Output Touchstone file
                    string outTstoneFile = argv[4];
                    vector<size_t> indLayerPrint = { 0, 1 * sdb.getNumLayer() / 3, 2 * sdb.getNumLayer() / 3, sdb.getNumLayer() - 1 }; // {}; // Can use integer division
                    sdb.setDesignName(adb.findNames().back());
                    sdb.setOutTouchstone(outTstoneFile);
                    sdb.print(indLayerPrint);
                    bool sdbCouldDump = sdb.dumpTouchstone();
                    cout << "File ready at " << outTstoneFile << endl << endl;
                }
                else
                {
                    // Output Xyce subcircuit file
                    string outXyceFile = argv[4];
                    vector<size_t> indLayerPrint = { 0, sdb.getNumLayer() / 2, sdb.getNumLayer() - 1 }; // {}; // Can use integer division
                    sdb.setDesignName(adb.findNames().back());
                    sdb.setOutXyce(outXyceFile);
                    sdb.print(indLayerPrint);
                    sdbCouldDump = sdb.dumpXyce();
                    cout << "File ready at " << outXyceFile << endl << endl;
                }
            });
            taskL.name("Terminal / File Out");
            taskK.precede(taskL);

            // CPP-Taskflow Executor
            executor.run(taskflow);
            executor.wait_for_all();
#ifdef PRINT_TASKFLOW_GRAPH
            taskflow.dump(cout);
#endif
        }
        else
        {
            cerr << "Must pass a GDSII file, sim_input file, and blank Xyce file to write after \"-s\" or \"-sx\" flag" << endl;
            cerr << "Must pass a GDSII file, sim_input file, and blank SPEF file to write after \"-sp\" flag" << endl;
            cerr << "Must pass a GDSII file, sim_input file, and blank CITI file to write after \"-sc\" flag" << endl;
            cerr << "Must pass a GDSII file, sim_input file, and blank Touchstone file to write after \"-st\" flag" << endl;
            cerr << "Rerun with \"--help\" flag for details" << endl;
        }
    }
    else
    {
        cerr << "Between 1 and 4 arguments are required, use \"--help\" flag for details" << endl;
    }

    return 0;
}
