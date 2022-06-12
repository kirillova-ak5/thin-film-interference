/* FILE NAME   : ANIM.CPP
 * PURPOSE     : definitions
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 21.07.2017
 */

#include "anim.h"
#include "list_units.h"

/* Static member initializatoin */
ragl::anim ragl::anim::Instance;

/* Default constructor method
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
ragl::anim::anim( VOID ) : win(), render(win::hWnd), input(win::hWnd, win::MouseWheel), timer()
{
}

/* Destructor method
 *   ARGUMENTS: none.
 *   RETURNS  : none.
 */
ragl::anim::~anim( VOID )
{
  Units.Walk([](unit *Uni){ delete Uni; });
}

/* Getting anim method
 *   ARGUMENTS: none.
 *   RETURNS  : 
 *     - animation system reference
 *         static anim & Instance;
 */
ragl::anim * ragl::anim::GetAnim()
{
  return &Instance;
}

/* Operator<< (Add unit) method
 *   ARGUMENTS:
 *     - unit to addition
 *         const unit &Uni;
 *   RETURNS  : 
 *     - reference to changed anim
 *         anim & *this;
 */
ragl::anim & ragl::anim::operator<<( ragl::unit *Uni )
{
  Units << Uni;
  return *this;
} /* End of operator<< method */

/* Initialization method
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ragl::anim::Init( VOID )
{
  *this << new control(this, 0);
  IsInit = 1;
} /* End of 'Init' method */

/* Deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ragl::anim::Close( VOID )
{
} /* End of 'Close' method */

/* Change window size handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ragl::anim::Resize( VOID )
{
  render::Resize(W, H);
} /* End of 'Resize' method */

/* Erase background handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID ragl::anim::Erase( HDC hDC )
{
} /* End of 'Erase' method */

/* Paint window content function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID ragl::anim::Paint( HDC hDC )
{
} /* End of 'Paint' method */

/* Timer handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ragl::anim::Timer( VOID )
{
  Idle();
} /* End of 'Timer' method */

/* Activate handle function.
 * ARGUMENTS:
 *   - activation window flag:
 *       BOOL IsActive;
 * RETURNS: None.
 */
VOID ragl::anim::Activate( VOID )
{
} /* End of 'Activate' method */

/* Free CPU time handling function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ragl::anim::Idle( VOID )
{
  input::Response(win::MouseWheel);
  win::MouseWheel = 0;
  timer::Response();
  Units.Walk([this]( unit *Uni )
             {
               Uni->Response(this);
             });
  render::FrameStart();
  Units.Walk([this](unit *Uni)
             {
               Uni->Render(this);
             });
  render::FrameEnd();
  render::FrameCopy();
} /* End of 'Idle' method */

/* END OF 'ANIM.CPP' FILE */
