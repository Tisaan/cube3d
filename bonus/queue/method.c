/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:11:14 by von               #+#    #+#             */
/*   Updated: 2026/05/27 16:12:38 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

t_queue* create_queue(int capacity)
{
    t_queue *q = malloc(sizeof(t_queue));
    q->data = malloc(capacity * sizeof(t_point));
    q->front = q->rear = 0;
    q->capacity = capacity;
	pthread_mutex_init(&q->mutex, NULL);
    return q;
}

void enqueue(t_queue *q, t_point p)
{
	pthread_mutex_lock(&q->mutex);
	if (q->rear < q->capacity)
    	q->data[q->rear++] = p;
	pthread_mutex_unlock(&q->mutex);
}

t_point dequeue(t_queue *q)
{
	t_point	point;
	pthread_mutex_lock(&q->mutex);
	if (q->front < q->rear)
    	point = q->data[q->front++];
	else
		point = (t_point){-1, -1};
	pthread_mutex_unlock(&q->mutex);
	return point;
}

bool is_empty(t_queue *q)
{
	bool	empty;

	pthread_mutex_lock(&q->mutex);
	empty = q->front >= q->rear;
	pthread_mutex_unlock(&q->mutex);
    return empty;
}

void free_t_queue(t_queue *q)
{
	pthread_mutex_destroy(&q->mutex);
    free(q->data);
    free(q);
}