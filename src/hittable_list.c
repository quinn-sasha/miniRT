#include "hittable_list.h"
#include <stdlib.h>
#include <stdio.h>

// リストの初期化 (必要な物体の数 (capacity) を引数に取る)
t_hittable_list init_hittable_list(size_t capacity)
{
    t_hittable_list list;

    list.count = 0;
    list.capacity = capacity;

    // 必要なメモリを malloc で一度だけ確保
    if (capacity == 0)
        list.objects = NULL;
    else
        list.objects = (t_hittable *)malloc(sizeof(t_hittable) * list.capacity);
    // メモリ確保失敗のチェック
    if (capacity > 0 && list.objects == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for hittable list.\n");
        list.capacity = 0;
    }

    return list;
}

// t_hittable の初期化 (変更なし)
t_hittable init_hittable(void *obj, t_hit_func hit_func)
{
    t_hittable hittable;
    hittable.object = obj;
    hittable.hit_func = hit_func;
    return hittable;
}

// リストに物体を追加 (容量オーバーチェック付き)
void hittable_list_add(t_hittable_list *list, t_hittable obj)
{
    // 容量チェック (事前に確保したサイズを超えていないか)
    if (list->count >= list->capacity)
    {
        fprintf(stderr, "Warning: Hittable list is full (Capacity: %zu). Object not added.\n", list->capacity);
        return;
    }

    // 物体を追加
    list->objects[list->count] = obj;
    list->count++;
}

// リストのメモリを解放 (変更なし)
void hittable_list_clear(t_hittable_list *list)
{
    if (list->objects)
    {
        free(list->objects);
    }
    list->objects = NULL;
    list->count = 0;
    list->capacity = 0;
}

// リスト全体の衝突判定 (ロジックは変更なし)
bool hit_hittable_list(
    const t_ray ray,
    double min_t,
    double max_t,
    t_hit_record *hit_rec,
    const t_hittable_list *list
)
{
    t_hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = max_t;

    for (size_t i = 0; i < list->count; i++)
    {
        t_hittable current_obj = list->objects[i];

        if (current_obj.hit_func(ray, min_t, closest_so_far, &temp_rec, current_obj.object))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *hit_rec = temp_rec;
        }
    }

    return hit_anything;
}
