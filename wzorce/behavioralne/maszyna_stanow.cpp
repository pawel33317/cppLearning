#include <iostream>
#include <memory>
#include <map>
#include <utility>
#include <string>
using namespace std;

// /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app __w_maszyna_stanow.cpp && ./app
enum class ProcessState{
    Inactive,
    Active,
    Paused,
    Terminated
};
enum class Command{
    Begin,
    End,
    Pause,
    Resume,
    Exit
};


class Process{
    class StateTransition //przejścia stanów
    {
        ProcessState mProcessState;
        Command mCommand;
    public:
        StateTransition(ProcessState ps, Command c)
        : mProcessState(ps), mCommand(c)
        {}
        bool operator<(const Process::StateTransition& other) const //!!!! const
        {
            if (mProcessState !=  other.mProcessState)
                return static_cast<int>(mProcessState) 
                    < static_cast<int>(other.mProcessState);
            return
                static_cast<int>(mCommand) 
                    < static_cast<int>(other.mCommand);
        }
    };
    map<StateTransition, ProcessState> mTransitions;
    ProcessState mCurrentState;
public:
    Process()
    {
        mCurrentState = ProcessState::Inactive;
        mTransitions.insert({
            {StateTransition{ProcessState::Inactive, Command::Exit},
            ProcessState::Terminated},
            {StateTransition{ProcessState::Inactive, Command::Begin},
            ProcessState::Active},
            {StateTransition{ProcessState::Active, Command::End},
            ProcessState::Inactive},
            {StateTransition{ProcessState::Active, Command::Pause},
            ProcessState::Paused},
            {StateTransition{ProcessState::Paused, Command::End},
            ProcessState::Inactive},
            {StateTransition{ProcessState::Paused, Command::Resume},
            ProcessState::Active}
            });
    }
    ProcessState getCurrentState(){ return mCurrentState; }
    ProcessState getNext(Command command)
    {
        StateTransition stateTransition{mCurrentState, command};
        ProcessState nextState;
        try
        {
            nextState = mTransitions.at(stateTransition);
        }
        catch(std::out_of_range& e)
        {
            throw("Invalid transition"s);
        }
        return nextState;
    }
    ProcessState moveNext(Command command)
    {
        mCurrentState = getNext(command);
        return mCurrentState;
    }
};


int main()
{
    cout << "-----w_maszyna_stanow-----" << endl;

    //https://dev.to/karn/building-a-simple-state-machine-in-python
    //https://www.codeproject.com/Articles/43356/A-Simple-State-Machine
    //https://stackoverflow.com/questions/5923767/simple-state-machine-example-in-c

    //4 stany: Inactive, Active, Paused, Terminated
    //5 przejść - command: Begin, End, Pause, Resume, Exit

    //W skrócie
    // class PrzejscieStanu
    //     Stan
    //     Komenda
    // class Proces
    //     TabelaPrzejść {PrzejscieStanu, Stan}
    //         //czyli ze stanu w PrzejscieStanu z użyciem
    //         //komendy w PrzejscieStanu otrzymujemy stan Stan
    //     AktualnyStan
    //     ZmienStan: AktualnyStan = TabelaPrzejść[staryStan, komenda]

    Process p{};
    cout << "Aktualne stan: " << (int)p.getCurrentState() << endl;
    p.moveNext(Command::Begin);
    cout << "Aktualne stan: " << (int)p.getCurrentState() << endl;
    try
    {
        p.moveNext(Command::Begin);
    }
    catch (const std::string&)
    {
        cout << "Nie można przejść ze stanu: " << (int)p.getCurrentState()
             << " do innego używając komendy Begin" << endl;
    }
    p.moveNext(Command::Pause);
    cout << "Aktualne stan: " << (int)p.getCurrentState() << endl;
    p.moveNext(Command::End);
    cout << "Aktualne stan: " << (int)p.getCurrentState() << endl;
    p.moveNext(Command::Exit);
    cout << "Aktualne stan: " << (int)p.getCurrentState() << endl;
}
