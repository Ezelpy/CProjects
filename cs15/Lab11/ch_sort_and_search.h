/*
 * ch_sort_and_search.h
 *
 * Course: EN47
 * Last updated: August 1, 2001
 *
 */
#include "en47_vis_txt.h"
#ifndef CH_SORT_AND_SEARCH_H
#define CH_SORT_AND_SEARCH_H

void ch_merge_sort(patient values[], int lo, int hi, patient spare[], int x_data, int y_data);
void ch_merge(patient values[], int begin0, int end0, int begin1, int end1, patient spare[], int x_data, int y_data);

int ch_binary_search(patient values[], int lo, int hi, patient query, 
		     bool reverse, int x_data, int y_data);

#endif
