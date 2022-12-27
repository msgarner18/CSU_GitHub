<?php
/**
 * @package    Fuel
 * @version    1.8.2
 * @author     Emmet Pritchard and Mark Garner
 */

/**
 * The M1 Controller.
 * @package  app
 * @extends  Controller
 */
class Controller_Milestone1 extends Controller_Template {
	/**
	 * The basic welcome message
	 *
	 * @access  public
	 * @return  Response
	 */
	public function action_index() {
		$data = array();
		$this->template->title = "Home Page";
		$this->template->content = View::forge('milestone1/index', $data);
	}

    public function action_about() {
        $data = array();
		$this->template->title = "About Page";
		$this->template->content = View::forge('milestone1/about', $data);
    }

	public function action_colorCoordinate() {
		$data = array();
		$this->template->title = "Color Coordinate";
		$this->template->content = View::forge('milestone1/colorCoordinate/colorCoordinate', $data);
	}
}