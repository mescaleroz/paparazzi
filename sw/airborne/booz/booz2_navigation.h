#ifndef BOOZ2_NAVIGATION_H
#define BOOZ2_NAVIGATION_H

#include "std.h"
#include "booz_geometry_int.h"

extern struct Pprz_int32_lla booz2_navigation_target;
extern struct Pprz_int32_lla booz2_navigation_carrot;

extern struct Pprz_int32_lla waypoints[];

extern void booz2_nav_init(void);
extern void booz2_nav_run(void);

extern uint16_t stage_time, block_time;

extern uint8_t nav_stage, nav_block;
extern uint8_t last_block, last_stage;
extern uint8_t last_wp __attribute__ ((unused));

extern int32_t ground_alt, nav_altitude;

void nav_init_stage(void);
void nav_init_block(void);
void nav_goto_block(uint8_t block_id);
void compute_dist2_to_home(void);
unit_t nav_reset_reference( void ) __attribute__ ((unused));
unit_t nav_update_waypoints_alt( void ) __attribute__ ((unused));
void nav_periodic_task_10Hz(void);
void nav_move_waypoint(uint8_t wp_id, struct Pprz_int32_lla new_pos);

void nav_home(void);

#define InitStage() nav_init_stage();

#define Block(x) case x: nav_block=x;
#define NextBlock() { nav_block++; nav_init_block(); }
#define GotoBlock(b) { nav_block=b; nav_init_block(); }

#define Stage(s) case s: nav_stage=s;
#define NextStageAndBreak() { nav_stage++; InitStage(); break; }
#define NextStageAndBreakFrom(wp) { last_wp = wp; NextStageAndBreak(); }

#define Label(x) label_ ## x:
#define Goto(x) { goto label_ ## x; }
#define Return() ({ nav_block=last_block; nav_stage=last_stage; block_time=0; FALSE;})

#define And(x, y) ((x) && (y))
#define Or(x, y) ((x) || (y))
#define Min(x,y) (x < y ? x : y)
#define Max(x,y) (x > y ? x : y)
#define LessThan(_x, _y) ((_x) < (_y))

/** Time in s since the entrance in the current block */
#define NavBlockTime() (block_time)

#define NavSetGroundReferenceHere() ({ nav_reset_reference(); nav_update_waypoints_alt(); FALSE; })

#define NavSetWaypointHere(_wp) { FALSE; }

#define NavCircleWaypoint(wp, radius) {}

/** Normalize a degree angle between 0 and 359 */
#define NormCourse(x) { \
  while (x < 0) x += 360; \
  while (x >= 360) x -= 360; \
}

#define NavCircleCount() {}
#define NavCircleQdr() {}

/** True if x (in degrees) is close to the current QDR (less than 10 degrees)*/
#define NavQdrCloseTo(x) {}
#define NavCourseCloseTo(x) {}

#define WaypointX(_wp) (waypoints[_wp].lon)
#define WaypointY(_wp) (waypoints[_wp].lat)
#define WaypointAlt(_wp) (waypoints[_wp].alt)

/*********** Navigation to  waypoint *************************************/
#define NavGotoWaypoint(_wp) { \
  PPRZ_INT32_LLA_COPY( booz2_navigation_target, waypoints[_wp]); \
}

#define NavGlide(_last_wp, _wp) {}

/*********** Navigation along a line *************************************/
#define NavSegment(_start, _end) {}
/*
extern void nav_route_xy(int32_t last_wp_lat, int32_t last_wp_lon, int32_t wp_lat, int32_t wp_lon);
#define NavSegment(_start, _end) \
  nav_route_xy(waypoints[_start].lat, waypoints[_start].lon, waypoints[_end].lat, waypoints[_end].lon)
*/

bool_t nav_approaching_from(uint8_t wp_idx, uint8_t from_idx);
#define NavApproaching(wp, time) nav_approaching_from(wp, 0)
#define NavApproachingFrom(wp, from, time) nav_approaching_from(wp, from)

/** Set the climb control to auto-throttle with the specified pitch
    pre-command */
#define NavVerticalAutoThrottleMode(_pitch) {}

/** Set the climb control to auto-pitch with the specified throttle
    pre-command */
#define NavVerticalAutoPitchMode(_throttle) {}

/** Set the vertical mode to altitude control with the specified altitude
 setpoint and climb pre-command. */
#define NavVerticalAltitudeMode(_alt, _pre_climb) { \
  nav_altitude = _alt; \
}

/** Set the vertical mode to climb control with the specified climb setpoint */
#define NavVerticalClimbMode(_climb) {}

/** Set the vertical mode to fixed throttle with the specified setpoint */
#define NavVerticalThrottleMode(_throttle) {}

#define NavHeading(_course) {}

#define NavAttitude(_roll) {}

#define nav_IncreaseShift(x) {}

#define nav_SetNavRadius(x) {}

#endif /* BOOZ2_NAVIGATION_H */