import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'main-page',
      component: require('@/components/MainPage').default
    },
    {
      path: '/showresult',
      name: 'showresult-page',
      component: require('@/components/SearchResult').default
    },
    {
      path: '/addTrainNumber',
      name: 'addTrainNumber-page',
      component: require('@/components/Admin').default
    }
  ]
})
