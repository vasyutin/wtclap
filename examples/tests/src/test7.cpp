// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

#include <string>
#include "wtclap/CmdLine.h"

using namespace TCLAP;
using namespace std;

int wmain(int argc, wchar_t **argv) {
    // Wrap everything in a try block.  Do this every time,
    // because exceptions will be thrown for problems.
    try {
        // Define the command line object.
        CmdLine cmd(
            L"Command description message. This is a long multi-line message "
            L"meant to test line wrapping.  This is more text that doesn't "
            L"really do anything besides take up lots of space that otherwise "
            L"might be used for something real.  That should be enough, don't "
            L"you think?",
            L' ', L"0.9");

        vector<wstring> allowed;
        allowed.push_back(L"homer");
        allowed.push_back(L"marge");
        allowed.push_back(L"bart");
        allowed.push_back(L"lisa");
        allowed.push_back(L"maggie");
        ValuesConstraint<wstring> vallowed(allowed);

        MultiArg<wstring> nameArg(L"n", L"name",
                                 L"Name to print. This is a long, nonsensical "
                                 L"message to test line wrapping.  Hopefully it "
                                 L"works.",
                                 true, &vallowed);
        cmd.add(nameArg);

        vector<int> iallowed;
        iallowed.push_back(1);
        iallowed.push_back(2);
        iallowed.push_back(3);
        ValuesConstraint<int> iiallowed(iallowed);

        UnlabeledMultiArg<int> intArg(L"times", L"Number of times to print",
                                      false, &iiallowed);
        cmd.add(intArg);

        // Ignore the names and comments!  These  args mean nothing (to this
        // program) and are here solely to take up space.
        ValueArg<int> gapCreate(L"f", L"gapCreate", L"The cost of creating a gap",
                                false, -10, L"negative int");
        cmd.add(gapCreate);

        ValueArg<int> gapExtend(L"g", L"gap-Extend",
                                L"The cost for each extension of a gap", false,
                                -2, L"negative int");
        cmd.add(gapExtend);

        SwitchArg dna(L"d", L"isDna", L"The input sequences are DNA", false);
        cmd.add(dna);

        ValueArg<wstring> scoringMatrixName(L"s", L"scoring--Matrix",
                                           L"Scoring Matrix name", false,
                                           L"BLOSUM50", L"name string");
        cmd.add(scoringMatrixName);

        ValueArg<wstring> seq1Filename(L"x", L"filename1",
                                      L"Sequence 1 filename (FASTA format)",
                                      false, L"", L"filename");
        cmd.add(seq1Filename);

        ValueArg<wstring> seq2Filename(L"z", L"filename2",
                                      L"Sequence 2 filename (FASTA format)",
                                      false, L"", L"filename");
        cmd.add(seq2Filename);

        ValueArg<float> lowerBound(L"b", L"lowerBound", L"lower percentage bound",
                                   false, 1.0, L"float lte 1");
        cmd.add(lowerBound);

        ValueArg<float> upperBound(L"u", L"upperBound", L"upper percentage bound",
                                   false, 1.0, L"float lte 1");
        cmd.add(upperBound);

        ValueArg<int> limit(L"l", L"limit", L"Max number of alignments allowed",
                            false, 1000, L"int");
        cmd.add(limit);

        argv[0] = const_cast<wchar_t *>(
            L"ThisIsAVeryLongProgramNameDesignedToTestSpacePrintWhichUsedToHaveP"
            L"roblemsWithLongProgramNamesIThinkItIsNowLongEnough");

        // Parse the args.
        cmd.parse(argc, argv);

        // Get the value parsed by each arg.
        vector<int> num = intArg.getValue();

        for (unsigned int i = 0; i < num.size(); i++)
            wcout << L"Got num " << num[i] << endl;

        vector<wstring> name = nameArg.getValue();

        for (unsigned int i = 0; i < name.size(); i++)
            wcout << L"Got name " << name[i] << endl;

    } catch (ArgException &e)  // catch any exceptions
    {
        wcerr << L"error: " << e.error() << L" for arg " << e.argId() << endl;
    }
}
