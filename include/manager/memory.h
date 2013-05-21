/*!
 *	\file memory.h
 *	\author André & Laury
 *	\version 0.1
 *	\date 21/05/13
 *	
 *	\brief Gestionnaire de mémoire
 */

#ifndef MEMORY_MANAGER
#define MEMORY_MANAGER

#include <stdlib.h>
#include <stdio.h>

/**
 * \struct _allocatedMemory AllocatedMemory
 * \brief Liste chainée de pointeurs alloués
 *	
 */
typedef struct _allocatedMemory {
	void* data;						/*!< Pointeur vers la mémoire allouée */
	size_t size;					/*!< Taille de la mémoire allouée */
	unsigned int refCount;			/*!< Nombre de références vers le pointeur*/
	struct _allocatedMemory* next;	/*!< Bloc de donnée suivant */
} AllocatedMemory;

/*!
 * \fn void* allocatePtr(size_t size)
 * \brief retourne un pointeur valide pointant vers une zone de taille size.
 *
 * \param size taille à allouer
 */
void* allocatePtr(size_t size);

/*!
 * \fn void deallocatePtr(void* ptr)
 * \brief libère la mémoire pointée
 *
 * \param ptr pointeur à libérer.
 */
void deallocatePtr(void* ptr);

/*!
 * \fn void* grabPtr(void* ptr)
 * \brief augmente le nombre de références vers le pointeur ptr
 *
 * \param ptr pointeur à grab.
 */
void* grabPtr(void* ptr);

/*!
 * \fn void releasePtr(void* ptr)
 * \brief diminue le nombre de références vers le pointeur ptr
 *
 * \param ptr pointeur à libérer.
 */
void releasePtr(void* ptr);

/*!
 * \fn unsigned long int getAllocatedBytes()
 * \brief retourne le nombre de bytes alloués dans le memory manager.
 *
 * \return le nombre de bytes encore alloués.
 */
unsigned long int getAllocatedBytes();

/*!
 * \fn void clearMemoryManager()
 * \brief libère toute la mémoire allouée.
 *
 */
void clearMemoryManager();

#endif
