#ifndef C_SIMULATION_HPP
#define C_SIMULATION_HPP

#include "libs1.hpp"
#include "c_geometry.hpp"
#include "c_file_loader.hpp"
#include "c_drawtarget.hpp"
#include "c_allegromisc.hpp"

extern unsigned int g_max_anim_frame;
class c_world;

class c_simulation {
	public:
		bool m_goodbye; ///< should we exit the program
		unsigned long int m_frame_number; ///< current frame of animation
		unique_ptr<c_world> m_world; ///< all the objects in this world
		std::shared_ptr <FONT> s_font_allegl;

		c_simulation(t_drawtarget_type drawtarget_type); ///< create the simulation. choose the drawtarget type (drawing engine e.g. Allegro or OpenGL)
	//c_simulation(); // t_drawtarget_type drawtarget_type); ///< create the simulation. choose the drawtarget type (drawing engine e.g. Allegro or OpenGL)
		c_simulation(const c_simulation &) = delete;
		c_simulation& operator=(const c_simulation &) = delete;
		virtual ~c_simulation ();

		void init ();

		void main_loop ();
		bool get_is_pause();

		void set_world( unique_ptr<c_world> && world ); ///< takes this world and uses it

	private:

		t_drawtarget_type m_drawtarget_type; ///< the selected drawing target, implies the drawing mode. E.g. Allegro or OpenGL. Do not just change it after creation.

		// TODO disable if disabled allegro support
		// allegro details:

		BITMAP * m_screen; ///< not-owning "reference" to the allegro's SCREEN
		c_al_bitmap m_frame; ///< allegro frame buffer
		c_al_bitmap smallWindow; ///< allegro window for display text info


		shared_ptr<c_drawtarget> m_drawtarget; ///< drawing will be send to this
		shared_ptr<c_gui> m_gui; ///< the current GUI

		volatile static bool close_button_pressed;

		// = false;
		void static c_close_button_handler () {
			close_button_pressed = true;
		}

		int get_move_object (); ///< return index of element in m_world->m_objects vector, -1 if not found

		bool simulation_pause;

		void process_input(); ///< process the input devices

		bool routingdemo();
		bool routingdemo_main();
};

#endif // C_SIMULATION_HPP
