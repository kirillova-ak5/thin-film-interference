/* FILE NAME   : RES.CPP
 * PURPOSE     : resource
 * PROGRAMMER  : AK5a.
 * LAST UPDATE : 24.07.2017
 */

#include "anim.h"

/* Apply material function.
  * ARGUMENTS: None.
  * RETURNS:
  *   (UINT) shader program Id;
  */
UINT ragl::material::Apply( VOID )
{
  ragl::render *rnd = anim::GetAnim();

  // Apply shader
  shader *shd = Shd;
  if (shd == NULL)
    shd = rnd->Shaders.Find("bin\\shaders\\def");
  assert(shd != NULL);
  UINT pid = shd->Apply();
  assert(pid != 0);

  INT loc;
  // Textures
  loc = glGetUniformLocation(pid, "IsTexture");
  if (Tex[0] != NULL)
  {
    glActiveTexture(GL_TEXTURE0);
    Tex[0]->Apply();
    if (loc != -1)
      glUniform1i(loc, 1);
  }
  else
    if (loc != -1)
      glUniform1i(loc, 0);
  loc = glGetUniformLocation(pid, "IsTexture1");
  if (Tex[1] != NULL)
  {
    glActiveTexture(GL_TEXTURE1);
    Tex[1]->Apply();
    if (loc != -1)
      glUniform1i(loc, 1);
    glActiveTexture(GL_TEXTURE0);
  }
  else
    if (loc != -1)
      glUniform1i(loc, 0);

  // Illumination coefficients
  if ((loc = glGetUniformLocation(pid, "Ka")) != -1)
    glUniform3fv(loc, 1, (FLT *)Ka);
  if ((loc = glGetUniformLocation(pid, "Kd")) != -1)
    glUniform3fv(loc, 1, (FLT *)Kd);
  if ((loc = glGetUniformLocation(pid, "Ks")) != -1)
    glUniform3fv(loc, 1, (FLT *)Ks);
  if ((loc = glGetUniformLocation(pid, "Ph")) != -1)
    glUniform1f(loc, Ph);
  if ((loc = glGetUniformLocation(pid, "Trans")) != -1)
    glUniform1f(loc, Trans);
  return pid;
} /* End of 'ragl::material::Apply' function */

/* END OF 'RES.CPP' FILE */
