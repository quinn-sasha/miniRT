#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hit_record.h"
#include <stdlib.h>
#include <stdbool.h>

#define NUM_SCENE_OBJECTS 10000

typedef struct s_hittable
{
	void	*object;

	//その物体固有の衝突判定関数へのポインタ (t_hit_func)
	t_hit_func hit_func;
} t_hittable;

typedef struct s_hittable_list
{
	t_hittable *objects; //t_hittable の動的配列へのポインタ
	size_t	count;       //現在リストに登録されている物体の数
	size_t	capacity;    //必要な物体の数
} t_hittable_list;

//リストの初期化
t_hittable_list	init_hittable_list(size_t capacity);

//リストに物体を追加
void	hittable_list_add(t_hittable_list *list, t_hittable obj);

//　t_hittableの初期化
t_hittable	init_hittable(void *obj, t_hit_func hit_func);


//リスト全体の衝突判定
bool	hit_hittable_list(
			const t_ray ray,
			double	min_t,
			double	max_t,
			t_hit_record	*hit_rec,
			const	t_hittable_list	*list
);

void	hittable_list_clear(t_hittable_list *list);

#endif
