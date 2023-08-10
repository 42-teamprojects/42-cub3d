#include "mlx/include/MLX42/MLX42.h"
#include <math.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TICK 30
#define CELL_SIZE 32
#define FOV M_PI / 3
#define COLORS_FLOOR 0xd52b1e
#define COLORS_CEILING 0xffffff
#define COLORS_WALL 0x013aa6
#define COLORS_WALL_DARK 0x012975
#define COLORS_RAYS 0xffa600

const int map[7][7] = {
    {1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1}};

typedef struct s_player
{
  double x;
  double y;
  double angle;
  double speed;
} t_player;

typedef struct s_ray
{
  double angle;
  double distance;
  int vertical;
} t_ray;

typedef struct s_game
{
  mlx_t *mlx;
  mlx_image_t *img_map;
  t_player player;
} t_game;

t_game *g_game;

void clear_screen(mlx_t *mlx, void *win)
{
  //   mlx_string_put(mlx, win, 0, 0, 0xFF0000, "Hello, world!");
}

void render_minimap(mlx_image_t *img, t_player *player, t_ray *rays)
{
  int cell_size = CELL_SIZE / 2;
  for (int y = 0; y < 7; y++)
  {
    for (int x = 0; x < 7; x++)
    {
      if (map[y][x])
        mlx_put_pixel(img, x * cell_size, y * cell_size, 0x808080);
    }
  }
  mlx_put_pixel(img, player->x / 2, player->y / 2, 0x0000FF);
  for (int i = 0; i < SCREEN_WIDTH; i++)
  {
    t_ray ray = rays[i];
    int color = COLORS_RAYS;
    if (ray.vertical)
      color = COLORS_WALL_DARK;
    mlx_put_pixel(img, ray.distance * cos(ray.angle) / 2 + player->x / 2, ray.distance * sin(ray.angle) / 2 + player->y / 2, color);
  }
}

void move_player(t_player *player)
{
  player->x += cos(player->angle) * player->speed;
  player->y += sin(player->angle) * player->speed;
}

double fix_fisheye(double distance, double angle, double player_angle)
{
  double diff = angle - player_angle;
  return distance * cos(diff);
}

int normalize_angle(double rayAngle)
{
  if (rayAngle < 0)
    rayAngle = (2 * M_PI) + rayAngle;
  else if (rayAngle > 2 * M_PI)
    rayAngle = rayAngle - (2 * M_PI);
  return (rayAngle);
}

t_ray cast_ray(double angle, t_player *player)
{
  // int right = (int)(fabs(floor((angle - M_PI / 2) / M_PI)) % 2);
  int right = normalize_angle(angle);
  double first_x = right ? floor(player->x / CELL_SIZE) * CELL_SIZE + CELL_SIZE : floor(player->x / CELL_SIZE) * CELL_SIZE;
  double first_y = player->y + (first_x - player->x) * tan(angle);
  double x_a = right ? CELL_SIZE : -CELL_SIZE;
  double y_a = x_a * tan(angle);
  int wall = 0;
  double next_x = first_x;
  double next_y = first_y;
  while (!wall)
  {
    int cell_x = right ? floor(next_x / CELL_SIZE) : floor(next_x / CELL_SIZE) - 1;
    int cell_y = floor(next_y / CELL_SIZE);
    if (cell_x < 0 || cell_x >= 7 || cell_y < 0 || cell_y >= 7)
      break;
    wall = map[cell_y][cell_x];
    if (!wall)
    {
      next_x += x_a;
      next_y += y_a;
    }
  }
  t_ray ray = {
      .angle = angle,
      .distance = sqrt(pow(next_x - player->x, 2) + pow(next_y - player->y, 2)),
      .vertical = right};
  return ray;
}

// void render_scene(void *mlx, void *win, t_player *player, t_ray *rays)
// {
//   for (int i = 0; i < SCREEN_WIDTH; i++)
//   {
//     t_ray ray = rays[i];
//     double distance = fix_fisheye(ray.distance, ray.angle, player->angle);
//     double wall_height = (CELL_SIZE * 5 / distance) * 277;
//     int color = ray.vertical ? COLORS_WALL_DARK : COLORS_WALL;
//     mlx_line_put(mlx, win, i, SCREEN_HEIGHT / 2 - wall_height / 2, i, SCREEN_HEIGHT / 2 + wall_height / 2, color);
//     mlx_line_put(mlx, win, i, 0, i, SCREEN_HEIGHT / 2 - wall_height / 2, COLORS_CEILING);
//     mlx_line_put(mlx, win, i, SCREEN_HEIGHT / 2 + wall_height / 2, i, SCREEN_HEIGHT, COLORS_FLOOR);
//   }
// }

void ft_hook(void *param)
{
  (void)param;
  float move_speed;
  float rot_speed;

  move_speed = 0.5;
  rot_speed = 0.05;

  // if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
  //   mlx_close_window(mlx);
  // if (mlx_is_key_down(mlx, MLX_KEY_W))
  //   move_forward(move_speed);
  // if (mlx_is_key_down(mlx, MLX_KEY_S))
  //   move_backward(move_speed);
  // if (mlx_is_key_down(mlx, MLX_KEY_A))
  //   move_left(move_speed);
  // if (mlx_is_key_down(mlx, MLX_KEY_D))
  //   move_right(move_speed);
  // if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
  // {
  //   g_game->player.angle -= rot_speed;
  // }
  // if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
  // {
  //   g_game->player.angle += rot_speed;
  // }
  t_ray rays[SCREEN_WIDTH];
  double initial_angle = g_game->player.angle - FOV / 2;
  double angle_step = FOV / SCREEN_WIDTH;
  for (int i = 0; i < SCREEN_WIDTH; i++)
  {
    double angle = initial_angle + i * angle_step;
    rays[i] = cast_ray(angle, &g_game->player);
  }
  render_minimap(g_game->img_map, &g_game->player, rays);
}

int main(void)
{
  mlx_t *mlx;
  mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", 1);
  g_game = (t_game *)malloc(sizeof(t_game));
  g_game->img_map = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
  mlx_image_to_window(mlx, g_game->img_map, 0, 0);
  t_player player = {
      .x = CELL_SIZE * 1.5,
      .y = CELL_SIZE * 2,
      .angle = 0,
      .speed = 0};
  g_game->player = player;
  // move_player(&player);

  // render_scene(mlx, win, &player, rays);

  mlx_loop_hook(mlx, ft_hook, g_game);
  mlx_loop(mlx);
  mlx_terminate(mlx);
  return 0;
}
