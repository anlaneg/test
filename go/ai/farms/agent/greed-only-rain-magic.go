package agent

import (
	"github.com/anlaneg/frame/frame"
	//"fmt"
)

/*这个agent会建造自已的保护区和任何空着的公共区，同时在cd时间内总对自已的保护区下雨*/
type GreedOnlyRainMaigcAgent struct {
	//name string
	//index int
	frame.Agent
	//frame.AgentMethod
}

func (protect *GreedOnlyRainMaigcAgent) Init() {
	//protect.index = 0
}

func (protect *GreedOnlyRainMaigcAgent) GetRequest() *frame.Request {
	limit := (frame.GAMEMAP_MAX_COLUMNS - frame.GAMEMAP_MAX_PROTECT_COLUMNS) * frame.GAMEMAP_MAX_ROWS
	for index := 0; index < limit ; index++ {
		row := index % frame.GAMEMAP_MAX_ROWS
		column := index / frame.GAMEMAP_MAX_ROWS
		if frame.AgentWhatAt(protect,row,column) == frame.PlaceType_none {
			//发现有空闲
			return &frame.Request{Name:frame.PlaceType_garden,Row:row,Column:column}
		}
	}
	
	//所有空均被占满了
	return nil
}

func (protect *GreedOnlyRainMaigcAgent) GetMagic() interface{} {
	/*rain for protect area*/
	return &frame.Rain{Column:1}
}