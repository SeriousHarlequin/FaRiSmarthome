<template>
    <AppHeader />
    <div class="layout">
        <div id="Page">
            <slot />
        </div>
    </div>
    <AppFooter />
</template>

<style>
    #Page {
        display: flex;
        justify-content: center; /* Center horizontally */
    }

    .layout {
        display: flex;
        flex-direction: column;
        min-height: 100vh;

    }
</style>