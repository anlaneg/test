#include <stdint.h>

//协议用protobuf来做

game_client_t (client = client + plugin )
game_server_t
game_plugin_t
game_user_t


int32_t game_main()
{
   game_client_t client = game_client_create();
   game_server_t server = client.game_servert_create("plugin_name");
   server.init();
   server.add_super_user(client);
   server.notify_game_ready();
   thread do
   {
	game_user_t user = server.accpect_game_user();
	if(!server.add_user(user))
        {
		//add user xx fail
                // response error message
        }	
   }

   server.notify_super_user_start_game();
   //wait all user load plugin start 

   while(!server.is_finish())
  {
	game_user_t current_user = server.select_user();
        server.notify_user_give_cards(current_user);
	server.wait_user_give();
        if(server.is_cards_ok())
        {
		server.rceive(cards);
	}

  }     
}
