
#include "game/boot.h"
#include "framework/framework.h"
#include "game/general/mainmenu.h"
#include "game/resources/gamecore.h"
#include <tuple>

namespace OpenApoc {

void BootUp::Begin()
{
	loadingimage = fw.data->load_image( "UI/LOADING.PNG" );
	logoimage = fw.data->load_image( "UI/LOGO.PNG" );
	loadtime = 0;
	fw.Display_SetTitle("OpenApocalypse");
}

void BootUp::Pause()
{
}

void BootUp::Resume()
{
}

void BootUp::Finish()
{
}

void BootUp::EventOccurred(Event *e)
{
	std::ignore = e;
}

void BootUp::Update(StageCmd * const cmd)
{
	loadtime++;
	loadingimageangle.Add( 5 );

	if(fw.gamecore == nullptr)
	{
		CreateGameCore(fw);
	}

	if(fw.gamecore && fw.gamecore->Loaded)
	{
		StartGame();
		cmd->cmd = StageCmd::Command::REPLACE;
		cmd->nextStage = std::make_shared<MainMenu>(fw);
	}
}

void BootUp::Render()
{
	int logow = fw.Display_GetWidth() / 3;
	float logosc = logow / (float)logoimage->size.x;
	
	Vec2<float> logoPosition {
		fw.Display_GetWidth()/2 - (logoimage->size.x * logosc / 2),
		fw.Display_GetHeight()/2 - (logoimage->size.y * logosc / 2)
	};
	Vec2<float> logoSize {
		logoimage->size.x * logosc,
		logoimage->size.y * logosc
	};

	fw.renderer->drawScaled(logoimage, logoPosition, logoSize);

	fw.renderer->drawRotated(loadingimage, Vec2<float>{24, 24}, Vec2<float>{fw.Display_GetWidth() - 50, fw.Display_GetHeight() - 50}, loadingimageangle.ToRadians() );
}

void BootUp::StartGame()
{
}

bool BootUp::IsTransition()
{
	return false;
}

void BootUp::CreateGameCore(Framework &fw)
{
	UString ruleset = fw.Settings->getString( "GameRules" );
	UString language = fw.Settings->getString( "Language" );

	fw.gamecore.reset(new GameCore(fw));

	fw.gamecore->Load(ruleset, language);
}

}; //namespace OpenApoc
