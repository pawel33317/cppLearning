#include <iostream>
#include <vector>
#include <memory>
using namespace std;
//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app state.cpp && ./app

//umożliwia pozwala na zmiane zachowania obiektu bazując poprzez podmianę klas ze zdefiniowanym
//kontekstem w tuntime

struct VideoPlayer;

struct VideoPlayerState { //StateBase - baza dla stanów, używana przez Context
    virtual void PlayButton(VideoPlayer*) = 0;
    virtual ~VideoPlayerState(){}
};

struct VideoPlayer //Context trzyma aktualny obiekt stanu, który zapewnia funkcjonalność
{                 //używany przez klienta, klent nie dotyka samego stanu
    std::unique_ptr<VideoPlayerState> mState;
    VideoPlayer(std::unique_ptr<VideoPlayerState>&& state) : mState(std::move(state)){}
    void PlayButton(){
        mState->PlayButton(this);
    }
};

//ConcreteState dostarcza funkcjonalność, która wykona kontekst, może zmieniać stan w kontekście ale nie musi
struct VideoPlayerState_STOPPED : public VideoPlayerState{
    void PlayButton(VideoPlayer* player) override;
};
struct VideoPlayerState_PLAYING : public VideoPlayerState{
    void PlayButton(VideoPlayer* player) override{
        cout << "Stopping playing" << endl;
        player->mState = std::make_unique<VideoPlayerState_STOPPED>();
    }
};
void VideoPlayerState_STOPPED::PlayButton(VideoPlayer* player) {
    cout << "Starting playing" << endl;
    player->mState = std::make_unique<VideoPlayerState_PLAYING>();
}

int main()
{
    VideoPlayer player(std::make_unique<VideoPlayerState_PLAYING>());
    player.PlayButton();
    player.PlayButton();
    player.PlayButton();
    player.PlayButton();
}



